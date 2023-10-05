//
//  Health.hpp
//  PleaseTanks
//
//  Created by Diniz Sá on 26/09/2023.
//

#pragma once

class Health {
    float maxHealth, currentHealth, armour;
    bool alive = true;
public:
    Health(float maxHealth, float armour);
    virtual ~Health(){};
    float updateHealth(float damage, float armourPenetration);
    float getCurrentHealth();
    float getMaxHealth();
    float getHealthRacio();
    bool isAlive();
};
