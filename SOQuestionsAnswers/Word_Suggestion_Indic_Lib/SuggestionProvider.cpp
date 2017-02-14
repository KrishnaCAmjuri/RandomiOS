//
// Created by bobble on 20/1/17.
//

#include <iostream>
#include "jsoncpp/json.h"
#include "SuggestionProvider.h"

std::vector<std::string> SuggestionProvider::getSuggestions(int numSuggestions, int *inputCodePoints, int inputSize,
                                                        PrevWordsInfo *prevWordsInfo, SuggestOptions *suggestOptions) {
    SuggestionResults *outSuggestionResults = new SuggestionResults(numSuggestions);

    int currentCode = inputCodePoints[inputSize - 1];
    ProximityProvider::KeyCoordinate *coordinate = proximityProvider->getKeyCoordinate(currentCode);
    mXCoords[inputSize - 1] = (int)coordinate->x;
    mYCoords[inputSize - 1] = (int)coordinate->y;

    dictionary->getSuggestions(proximityProvider->getProximity(currentCode), traverseSession,
                               mXCoords, mYCoords, mTimes, mPointerIds,
                               inputCodePoints, inputSize, prevWordsInfo, suggestOptions,
                               LANGUAGE_WEIGHT, outSuggestionResults);

    std::priority_queue<
            SuggestedWord,
            std::vector<SuggestedWord>,
            SuggestedWord::Comparator> words = outSuggestionResults->getSuggestedWords();

    std::vector<std::string> suggestions;
    std::map<int, std::vector<std::string>, std::greater<int>> sortedMap;

    char inputWordBuf[50];
    intArrayToCharArray(inputCodePoints, inputSize, inputWordBuf, NELEMS(inputWordBuf));
    suggestions.push_back(std::string(inputWordBuf));

    while(!words.empty()) {
        char buf[50];
        intArrayToCharArray(words.top().getCodePoint(), words.top().getCodePointCount(), buf, NELEMS(buf));
        sortedMap[words.top().getScore()].push_back(std::string(buf));
        words.pop();
    }

    for (auto iterator = sortedMap.begin(); iterator != sortedMap.end(); iterator++) {
        for (auto item : iterator->second) {
            if (item != std::string(inputWordBuf))
                suggestions.push_back(item);
        }
    }

    return suggestions;
}

std::vector<std::string> SuggestionProvider::getEmptySuggestions(int numSuggestions, PrevWordsInfo *prevWordsInfo) {
    SuggestionResults *outSuggestionResults = new SuggestionResults(numSuggestions);

    dictionary->getPredictions(prevWordsInfo, outSuggestionResults);

    std::priority_queue<
            SuggestedWord,
            std::vector<SuggestedWord>,
            SuggestedWord::Comparator> words = outSuggestionResults->getSuggestedWords();

    std::vector<std::string> suggestions;
    std::map<int, std::vector<std::string>, std::greater<int>> sortedMap;

    while(!words.empty()) {
        char buf[50];
        intArrayToCharArray(words.top().getCodePoint(), words.top().getCodePointCount(), buf, NELEMS(buf));
        sortedMap[words.top().getScore()].push_back(std::string(buf));
        words.pop();
    }

    for (auto iterator = sortedMap.begin(); iterator != sortedMap.end(); iterator++) {
        for (auto item : iterator->second) {
            suggestions.push_back(item);
        }
    }

    return suggestions;
}

int SuggestionProvider::get_file_size(std::string &path) {
    std::ifstream in(path, std::ifstream::ate | std::ifstream::binary);
    return static_cast<int>(in.tellg());
}

SuggestionProvider::SuggestionProvider(const std::string &dictPath, const std::string &proximityPath) {
    // Create a new proximity provider
    proximityProvider = new ProximityProvider(proximityPath);

    // Get dict size
    std::string localDictPath = dictPath;
    int dictSize = get_file_size(localDictPath);

    // Create dict policy implementation
    DictionaryStructureWithBufferPolicy::StructurePolicyPtr dictionaryStructureWithBufferPolicy(
            DictionaryStructureWithBufferPolicyFactory::newPolicyForExistingDictFile(
                    localDictPath.c_str(), 0, dictSize, false));

    // Create dict instance
    dictionary = new Dictionary(std::move(dictionaryStructureWithBufferPolicy));


    traverseSession = (DicTraverseSession *) DicTraverseSession::getSessionInstance(dictSize);
}

SuggestionProvider::~SuggestionProvider() {
    delete dictionary;
    delete traverseSession;
    delete proximityProvider;
}
