//
//  Track.cpp
//  PleaseTanks
//
//  Created by Diniz Sá on 14/09/2023.
//

#include "Track.hpp"
#include "Utils.hpp"

Track::Track(sf::Vector2f size, int spriteIndex) : Body(size, size, SpriteNames::tracks, spriteIndex), index(0), traveledDistance(0.f) {
}

bool Track::translate(sf::Vector2f delta) {
    bool translated = Body::translate(delta);
    if (translated) {
        traveledDistance += Utils::getLength(delta.x, delta.y);
        index = fmod((traveledDistance / 1.f), 2.f) < 1.f ? (originSpriteIndex+1) : originSpriteIndex;
        setSprite(index);
    }
    return translated;
}
