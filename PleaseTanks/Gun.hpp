//
//  Hull.hpp
//  PleaseTanks
//
//  Created by Diniz Sá on 14/09/2023.
//

#pragma once

#include "Drawable.hpp"
#include "PhysicsBody.hpp"
#include "Health.hpp"
#include "AudioPlayer.hpp"
#include "AudioPlayer.hpp"
#include "CombatUnit.hpp"

class Gun : public PhysicsBody, public Drawable, private Health, public CombatUnit, private AudioPlayer {
private:
    void rotateGun(float speed);
    std::unique_ptr<Weapon> primaryWeapon;
    std::unique_ptr<Weapon> secondaryWeapon;
public:
    Gun(sf::Vector2f size, int spriteIndex);
    bool attack() override;
    void receiveDamage(int damage) override;
    void update() override;
};
