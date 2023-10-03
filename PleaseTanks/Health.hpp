//
//  Health.hpp
//  PleaseTanks
//
//  Created by Diniz Sá on 26/09/2023.
//

#pragma once

class Health {
    float maxHealth, currentHealth;
    bool alive = true;
public:
    Health(float maxHealth);
    virtual ~Health(){};
    float updateHealth(float delta);
    float getCurrentHealth();
    float getMaxHealth();
    float getHealthRacio();
    bool isAlive();
};
