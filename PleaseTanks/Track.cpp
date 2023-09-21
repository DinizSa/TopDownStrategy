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
    Drawable(imageSize, PhysicsBody::centerWorld, PhysicsBody::rotation, SpriteNames::tracks, spriteIndex),
    distanceToChangeSprite(20.f)
{
    setSpriteRange(spriteIndex, spriteIndex+1);
    
    traveledDistance.subscribe(this, [&](float distance) {
        if (fmod((distance / distanceToChangeSprite), 2.f) < 1.f) {
            setNextSprite();
        }
    });
}

Track::~Track() {
    traveledDistance.unsubscribe(this);
}
