//
//  Hull.hpp
//  PleaseTanks
//
//  Created by Diniz Sá on 14/09/2023.
//

#pragma once
#include "AutoSprite.hpp"
#include "PhysicsBody.hpp"
#include "Health.hpp"
#include "AudioPlayer.hpp"
#include "CombatUnit.hpp"

class Hull : public PhysicsBody, public Drawable, public CombatUnit, private AudioPlayer {
private:
    AutoSprite* exhaust;
    Subject<sf::Vector2f> exhaustPosition;
    float speed;
    AutoSprite* damageSmoke;
    int centerWorldObserverId, translatingObserverId;
public:
    Hull(sf::Vector2f size, int spriteIndex);
    ~Hull();
    void receiveDamage(int damage) override;
    void setSpeed(float newSpeed);
    float getSpeed() const;
};
