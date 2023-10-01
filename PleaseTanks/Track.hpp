//
//  Track.hpp
//  PleaseTanks
//
//  Created by Diniz Sá on 14/09/2023.
//

#pragma once

#include "PhysicsBody.hpp"
#include "AutoSprite.hpp"
#include "Health.hpp"
#include "CombatUnit.hpp"

class Track : public PhysicsBody, public AutoSprite, public CombatUnit, private Health {
private:
    float deltaTrack;
    float previousTrackDistance;
    
    float deltaTrail;
    float previousTrailDistance;
    
public:
    Track(sf::Vector2f size, int spriteIndex);
    void receiveDamage(int damage) override;
};
