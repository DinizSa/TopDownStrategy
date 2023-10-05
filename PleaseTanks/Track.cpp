//
//  Track.cpp
//  PleaseTanks
//
//  Created by Diniz Sá on 14/09/2023.
//

#include "Track.hpp"
#include "Utils.hpp"
#include "TrackTrail.hpp"

Track::Track(sf::Vector2f imageSize, int spriteIndex, float maxHealth, float armour) :
    PhysicsBody(imageSize),
    AutoSprite(imageSize, 1.f, {SpriteNames::tracks, spriteIndex, spriteIndex+1, 0, false}),
    CombatUnit(maxHealth, armour), framesDelta(10), framesCounter(0)
{
    setPosition(&centerWorld, &rotation);

    traveledDistanceObserverId = traveledDistance.subscribe([&](float distance) {
        if (framesCounter > framesDelta ) {
            setNextSprite();
            
            sf::Vector2f size = rect.getSize();
            new TrackTrail(size, 21, centerWorld(), rotation());
            framesCounter = 0;
        }
        framesCounter++;
    });
}
Track::~Track() {
    traveledDistance.unsubscribe(traveledDistanceObserverId);
}
void Track::receiveDamage(float damage, float armourPenetration) {
    updateHealth(damage, armourPenetration);
}
