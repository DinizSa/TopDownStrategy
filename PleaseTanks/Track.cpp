//
//  Track.cpp
//  PleaseTanks
//
//  Created by Diniz Sá on 14/09/2023.
//

#include "Track.hpp"
#include "Utils.hpp"

Track::Track(sf::Vector2f imageSize, int spriteIndex) :
    PhysicsBody(imageSize),
    Drawable(imageSize, PhysicsBody::centerWorld, PhysicsBody::rotation, SpriteNames::tracks, spriteIndex)
{}

bool Track::translate(sf::Vector2f delta) {
    bool translated = PhysicsBody::translate(delta);
    if (translated) {
        traveledDistance += Utils::getLength(delta.x, delta.y);
        if (fmod((traveledDistance / distanceToChangeSprite), 2.f) < 1.f) {
            setNextSprite();
        }
    }
    return translated;
}
