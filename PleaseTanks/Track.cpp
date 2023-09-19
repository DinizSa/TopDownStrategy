//
//  Track.cpp
//  PleaseTanks
//
//  Created by Diniz Sá on 14/09/2023.
//

#include "Track.hpp"
#include "Utils.hpp"

Track::Track(sf::Vector2f size) : Body(size, size, "/Users/Shared/merda/PleaseTanks/images/tracksSprites.png"), index(0), traveledDistance(0.f) {
    setTextureRect(0);
    setTextureSize({42.f, 246.f});
}

bool Track::translate(sf::Vector2f delta) {
    bool translated = Body::translate(delta);
    if (translated) {
        traveledDistance += Utils::getLength(delta.x, delta.y);
        index = fmod((traveledDistance / 1.f), 2.f) < 1.f ? 1 : 0;
        setTextureRect(index);
    }
    return translated;
}
