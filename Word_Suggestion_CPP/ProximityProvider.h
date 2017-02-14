//
// Created by kunaldawn on 25/1/17.
//

#ifndef BOBBLE_INDIC2_PROXIMITYPROVIDER_H
#define BOBBLE_INDIC2_PROXIMITYPROVIDER_H

#include "libDict/suggest/core/layout/proximity_info.h"

using latinime::ProximityInfo;

#include <vector>
#include <map>

class ProximityProvider {
public:
    class KeyCoordinate {
    public:
        const float x;
        const float y;

        KeyCoordinate(float x, float y):x(x), y(y) {}
    };

private:
    std::vector<ProximityInfo *> mProviderInstances;
    std::vector<KeyCoordinate *> mCoordinateInstances;
    std::map<int, ProximityInfo *> mCodeToProximityMap;
    std::map<int, KeyCoordinate *> mCodeToCoordinateMap;

    ProximityInfo *createNewProximityInstance(const std::string &path);

public:
    ProximityProvider(std::vector<std::string> fileList);
    ProximityProvider(const std::string &providerPath);
    ~ProximityProvider();
    ProximityInfo *getProximity(int keyCode);
    KeyCoordinate *getKeyCoordinate(int keyCode);
};


#endif //BOBBLE_INDIC2_PROXIMITYPROVIDER_H
