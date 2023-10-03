//
//  Soldier.hpp
//  PleaseTanks
//
//  Created by Diniz Sá on 30/09/2023.
//

#include <SFML/Graphics.hpp>

#include "PhysicsBody.hpp"
#include "AutoSprite.hpp"
#include "Observer.hpp"
#include "CombatUnit.hpp"
#include "Weapon.hpp"
#include "AudioPlayer.hpp"
#include "Health.hpp"

#pragma once

class Soldier : public PhysicsBody, public CombatUnit, private Observer, private AudioPlayer {
private:
    AutoSprite feet;
    AutoSprite soldierBody;
    std::shared_ptr<Weapon> primaryWeapon;
    std::shared_ptr<Weapon> secondaryWeapon;
    
    bool fireRifle();
    bool fireGrenade();
public:
    Soldier(sf::Vector2f size, sf::Vector2f position);
    ~Soldier();
    void update() override;
    void receiveDamage(int damage) override;
    bool attackPrimary() override;
    bool attackSecondary() override;
};
