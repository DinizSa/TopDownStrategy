//
//  CombatUnit.hpp
//  PleaseTanks
//
//  Created by Diniz Sá on 30/09/2023.
//

#pragma once

#include "Health.hpp"

class CombatUnit: public Health {
public:
    CombatUnit(float maxHealth): Health(maxHealth) {};
    virtual ~CombatUnit(){};
    virtual void receiveDamage(int damage) {};
    virtual bool attackPrimary() {return false;};
    virtual bool attackSecondary() {return false;};
};
