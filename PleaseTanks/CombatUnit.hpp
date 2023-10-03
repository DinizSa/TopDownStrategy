//
//  CombatUnit.hpp
//  PleaseTanks
//
//  Created by Diniz Sá on 30/09/2023.
//

#pragma once

class CombatUnit {
public:
    bool alive = true;
    virtual ~CombatUnit(){};
    virtual void receiveDamage(int damage) {};
    virtual bool attackPrimary() {return false;};
    virtual bool attackSecondary() {return false;};
};
