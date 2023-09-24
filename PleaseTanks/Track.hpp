//
//  Track.hpp
//  PleaseTanks
//
//  Created by Diniz Sá on 14/09/2023.
//

#pragma once

#include "PhysicsBody.hpp"
#include "AutoSprite.hpp"

class Track : public PhysicsBody, public AutoSprite {
private:
    float deltaTrack;
    float previousTrackDistance;
    
    float deltaTrail;
    float previousTrailDistance;
    
public:
    Track(sf::Vector2f size, int spriteIndex);
};
