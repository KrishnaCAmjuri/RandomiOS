//
// Created by kunaldawn on 25/1/17.
//

#include <iostream>
#include "ProximityProvider.h"
#include "FileUtils.h"

ProximityProvider::ProximityProvider(const std::string &providerPath) {
    std::vector<std::string> proximityFiles = FileUtils::getFiles(providerPath, true, ".json");

    // TODO : DEBUG
    std::cout << "num proximity files : " << proximityFiles.size() << std::endl;

    for (int index = 0; index < proximityFiles.size(); index++) {
        std::string fileName = proximityFiles[index];
        ProximityInfo *proximity = createNewProximityInstance(providerPath + "/" + fileName);
        mProviderInstances.push_back(proximity);
    }

}

ProximityProvider::~ProximityProvider() {
    mCodeToProximityMap.clear();
    for (int index = 0; index < mProviderInstances.size(); index++) {
        ProximityInfo *instance = mProviderInstances[index];
        delete instance;
    }
    mProviderInstances.clear();
}

ProximityInfo *ProximityProvider::createNewProximityInstance(const std::string &path) {

    Json::Value root = FileUtils::loadJson(path);

    std::string locale;
    int keyboardMinWidth;
    int keyboardHeight;
    int gridWidth;
    int gridHeight;
    int mostCommonKeyWidth;
    int mostCommonKeyHeight;
    int keyCount;
    int proximityCharsArrayLen;
    int charCodesLen;
    int charXCoordLen;
    int charYCoordLen;

    char *c_locale;

    int *proximityCharsArray;
    int *keyXCoordinates;
    int *keyYCoordinates;
    int *keyWidths;
    int *keyHeights;
    int *keyCharCodes;

    float *sweetSpotCenterXs;
    float *sweetSpotCenterYs;
    float *sweetSpotRadii;

    locale = root.get("locale", Json::stringValue).asString();
    keyboardMinWidth = root.get("keyboardMinWidth", Json::intValue).asInt();
    keyboardHeight = root.get("keyboardHeight", Json::intValue).asInt();
    gridWidth = root.get("gridWidth", Json::intValue).asInt();
    gridHeight = root.get("gridHeight", Json::intValue).asInt();
    mostCommonKeyWidth = root.get("mostCommonKeyWidth", Json::intValue).asInt();
    mostCommonKeyHeight = root.get("mostCommonKeyHeight", Json::intValue).asInt();
    keyCount = root.get("keyCount", Json::intValue).asInt();

    Json::Value arrayContainer;

    arrayContainer = root.get("proximityCharsArray", Json::arrayValue);
    proximityCharsArray = new int[arrayContainer.size()];
    proximityCharsArrayLen = arrayContainer.size();
    for (int index = 0; index < arrayContainer.size(); index++) {
        proximityCharsArray[index] = arrayContainer.get(index, Json::intValue).asInt();
    }

    arrayContainer = root.get("keyXCoordinates", Json::arrayValue);
    keyXCoordinates = new int[arrayContainer.size()];
    for (int index = 0; index < arrayContainer.size(); index++) {
        keyXCoordinates[index] = arrayContainer.get(index, Json::intValue).asInt();
    }

    arrayContainer = root.get("keyYCoordinates", Json::arrayValue);
    keyYCoordinates = new int[arrayContainer.size()];
    for (int index = 0; index < arrayContainer.size(); index++) {
        keyYCoordinates[index] = arrayContainer.get(index, Json::intValue).asInt();
    }

    arrayContainer = root.get("keyWidths", Json::arrayValue);
    keyWidths = new int[arrayContainer.size()];
    for (int index = 0; index < arrayContainer.size(); index++) {
        keyWidths[index] = arrayContainer.get(index, Json::intValue).asInt();
    }

    arrayContainer = root.get("keyHeights", Json::arrayValue);
    keyHeights = new int[arrayContainer.size()];
    for (int index = 0; index < arrayContainer.size(); index++) {
        keyHeights[index] = arrayContainer.get(index, Json::intValue).asInt();
    }

    arrayContainer = root.get("keyCharCodes", Json::arrayValue);
    keyCharCodes = new int[arrayContainer.size()];
    charCodesLen = arrayContainer.size();
    for (int index = 0; index < arrayContainer.size(); index++) {
        keyCharCodes[index] = arrayContainer.get(index, Json::intValue).asInt();
    }

    arrayContainer = root.get("sweetSpotCenterXs", Json::arrayValue);
    sweetSpotCenterXs = new float[arrayContainer.size()];
    charXCoordLen = arrayContainer.size();
    for (int index = 0; index < arrayContainer.size(); index++) {
        sweetSpotCenterXs[index] = arrayContainer.get(index, Json::realValue).asFloat();
    }

    arrayContainer = root.get("sweetSpotCenterYs", Json::arrayValue);
    sweetSpotCenterYs = new float[arrayContainer.size()];
    charYCoordLen = arrayContainer.size();
    for (int index = 0; index < arrayContainer.size(); index++) {
        sweetSpotCenterYs[index] = arrayContainer.get(index, Json::realValue).asFloat();
    }

    arrayContainer = root.get("sweetSpotRadii", Json::arrayValue);
    sweetSpotRadii = new float[arrayContainer.size()];
    for (int index = 0; index < arrayContainer.size(); index++) {
        sweetSpotRadii[index] = arrayContainer.get(index, Json::realValue).asFloat();
    }

    c_locale = new char[locale.length() + 1];
    strcpy(c_locale, locale.c_str());

    // Create proximity instance
    ProximityInfo *proximityInfo = new ProximityInfo(c_locale,
                                      keyboardMinWidth, keyboardHeight,
                                      gridWidth, gridHeight,
                                      mostCommonKeyWidth, mostCommonKeyHeight,
                                      proximityCharsArray, proximityCharsArrayLen, keyCount,
                                      keyXCoordinates, keyYCoordinates,
                                      keyWidths, keyHeights, keyCharCodes,
                                      sweetSpotCenterXs, sweetSpotCenterYs, sweetSpotRadii);

    // Update character mapping
    int limit = std::min(charCodesLen, std::min(charXCoordLen, charYCoordLen));
    for (int index = 0; index < limit; index++) {
        int code = keyCharCodes[index];
        float x = sweetSpotCenterXs[index];
        float y = sweetSpotCenterYs[index];
        KeyCoordinate *coordinate = new KeyCoordinate(x, y);
        mCoordinateInstances.push_back(coordinate);

        mCodeToProximityMap[code] = proximityInfo;
        mCodeToCoordinateMap[code] = coordinate;
    }

    return proximityInfo;
}

ProximityProvider::KeyCoordinate * ProximityProvider::getKeyCoordinate(int keyCode) {
    if (mCodeToCoordinateMap.find(keyCode) != mCodeToCoordinateMap.end()) {
        return mCodeToCoordinateMap[keyCode];
    }

    KeyCoordinate *newInstance = new KeyCoordinate(0, 0);
    mCoordinateInstances.push_back(newInstance);

    return newInstance;
}

ProximityInfo *ProximityProvider::getProximity(int keyCode) {
    if (mCodeToProximityMap.find(keyCode) != mCodeToProximityMap.end()) {
        return mCodeToProximityMap[keyCode];
    }

    if (mProviderInstances.size() > 0) {
        return mProviderInstances[0];
    }

    return nullptr;
}
