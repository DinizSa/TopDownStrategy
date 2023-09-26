//
//  Health.hpp
//  PleaseTanks
//
//  Created by Diniz Sá on 26/09/2023.
//

#pragma once

class Health {
    int maxHealth, currentHealth;
public:
    Health(int maxHealth);
    void updateHealth(int delta);
    void updateHealth(float delta);
};
