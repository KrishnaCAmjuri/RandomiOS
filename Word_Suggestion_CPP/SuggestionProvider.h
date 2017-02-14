//
// Created by bobble on 20/1/17.
//

#ifndef BOBBLE_INDIC2_INDICSUGGESTOR_H
#define BOBBLE_INDIC2_INDICSUGGESTOR_H

#include <string>
#include <vector>
#include <fstream>
#include "libDict/suggest/core/layout/proximity_info.h"
#include "libDict/suggest/core/session/dic_traverse_session.h"
#include "libDict/suggest/core/result/suggestion_results.h"
#include "libDict/suggest/policyimpl/dictionary/structure/dictionary_structure_with_buffer_policy_factory.h"
#include "ProximityProvider.h"

using latinime::Dictionary;
using latinime::SuggestedWord;
using latinime::ProximityInfo;
using latinime::PrevWordsInfo;
using latinime::SuggestOptions;
using latinime::SuggestionResults;
using latinime::DicTraverseSession;
using latinime::DictionaryStructureWithBufferPolicy;
using latinime::DictionaryStructureWithBufferPolicyFactory;

class SuggestionProvider {
private:
    float LANGUAGE_WEIGHT = -1.0f;

    int get_file_size(std::string &path);

    int mXCoords[48] = {};
    int mYCoords[48] = {};
    int mTimes[48] = {};
    int mPointerIds[48] = {};

    ProximityProvider *proximityProvider;
    Dictionary *dictionary;
    DicTraverseSession *traverseSession;
public:
    SuggestionProvider(const std::string &dictPath, const std::vector<std::string> &proximityPathVec);
    SuggestionProvider(const std::string &dictPath, const std::string &proximityPath);
    ~SuggestionProvider();
    std::vector<std::string> getSuggestions(int numSuggestions, int *inputCodePoints, int inputSize,
                                            PrevWordsInfo *prevWordsInfo, SuggestOptions *suggestOptions);
    std::vector<std::string> getEmptySuggestions(int numSuggestions, PrevWordsInfo *prevWordsInfo);
};


#endif //BOBBLE_INDIC2_INDICSUGGESTOR_H
