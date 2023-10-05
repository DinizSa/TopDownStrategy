//
//  CombatUnit.hpp
//  PleaseTanks
//
//  Created by Diniz Sá on 30/09/2023.
//

#pragma once

#include "Health.hpp"

class CombatUnit: public PhysicsBody, public Health {
public:
    CombatUnit(sf::Vector2f size, float maxHealth, float armour): PhysicsBody(size), Health(maxHealth, armour) {};
    virtual ~CombatUnit(){};
    virtual bool attackPrimary() {return false;};
    virtual bool attackSecondary() {return false;};
};
