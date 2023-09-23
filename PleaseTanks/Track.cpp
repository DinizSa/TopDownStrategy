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
    AutoSprite(imageSize, PhysicsBody::centerWorld, PhysicsBody::rotation, 1.f, {SpriteNames::tracks, spriteIndex, spriteIndex+1, 0, false}),
    distanceToChangeSprite(17.f), previousChangeDistance(0.f)
{
    traveledDistance.subscribe(this, [&](float distance) {
        if (distance > previousChangeDistance + distanceToChangeSprite ) {
            setNextSprite();
            previousChangeDistance = distance;
        }
    });
}

Track::~Track() {
    traveledDistance.unsubscribe(this);
}
