//
//  Health.hpp
//  PleaseTanks
//
//  Created by Diniz Sá on 26/09/2023.
//

#pragma once

class Health {
    float maxHealth, currentHealth;
public:
    Health(float maxHealth);
    virtual ~Health(){};
    void updateHealth(float delta);
    float getCurrentHealth();
    float getMaxHealth();
};
