//
//  Track.cpp
//  PleaseTanks
//
//  Created by Diniz Sá on 14/09/2023.
//

#include "Track.hpp"
#include "Utils.hpp"
#include "TrackTrail.hpp"

Track::Track(sf::Vector2f imageSize, int spriteIndex) :
    PhysicsBody(imageSize),
    AutoSprite(imageSize, 1.f, {SpriteNames::tracks, spriteIndex, spriteIndex+1, 0, false}),
    deltaTrack(17.f), previousTrackDistance(0.f), previousTrailDistance(0.f), deltaTrail(50)
{
    setPosition(&centerWorld, &rotation);

    traveledDistance.subscribe(this, [&](float distance) {
        std::cout << distance << '\n';
        if (distance > previousTrailDistance + deltaTrack ) {
            setNextSprite();
            previousTrailDistance = distance;
        }
        if (distance > previousTrackDistance + deltaTrail ) {
            new TrackTrail(21, centerWorld(), rotation());
            previousTrackDistance = distance;
        }
    });
}
