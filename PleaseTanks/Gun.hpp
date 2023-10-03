//
//  Hull.hpp
//  PleaseTanks
//
//  Created by Diniz Sá on 14/09/2023.
//

#pragma once

#include "PhysicsBody.hpp"
#include "Health.hpp"
#include "AudioPlayer.hpp"
#include "AudioPlayer.hpp"
#include "CombatUnit.hpp"
#include "Weapon.hpp"
#include "AutoSprite.hpp"

class Gun : public PhysicsBody, public Drawable, public CombatUnit, private AudioPlayer {
private:
    void rotateGun(float speed);
    std::shared_ptr<Weapon> primaryWeapon;
    std::shared_ptr<Weapon> secondaryWeapon;
    AutoSprite* damageSmoke;
    int triggerObserverId, rotatingLocalObserverId;
public:
    Gun(sf::Vector2f size, int spriteIndex);
    virtual ~Gun();
    bool attackPrimary() override;
    bool attackSecondary() override;
    void receiveDamage(int damage) override;
    void update() override;
};
