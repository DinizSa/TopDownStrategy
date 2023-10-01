//
//  CombatUnit.hpp
//  PleaseTanks
//
//  Created by Diniz Sá on 30/09/2023.
//

#pragma once

class CombatUnit {
public:
    virtual void receiveDamage(int damage) {};
    virtual void attack() {};
};
