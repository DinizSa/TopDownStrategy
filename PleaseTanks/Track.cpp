//
//  Track.cpp
//  PleaseTanks
//
//  Created by Diniz Sá on 14/09/2023.
//

#include "Track.hpp"
#include "Utils.hpp"

Track::Track(sf::Vector2f size, int spriteIndex) : Body(size, size, SpriteNames::tracks, spriteIndex), index(0), distanceToChangeSprite(2.f) {
}

bool Track::translate(sf::Vector2f delta) {
    bool translated = Body::translate(delta);
    if (translated) {
        traveledDistance += Utils::getLength(delta.x, delta.y);
        if (fmod((traveledDistance / distanceToChangeSprite), 2.f) < 1.f) {
            setNextSprite();
        }
    }
    return translated;
}
