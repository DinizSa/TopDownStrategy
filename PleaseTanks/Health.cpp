//
//  Health.cpp
//  PleaseTanks
//
//  Created by Diniz Sá on 26/09/2023.
//

#include "Health.hpp"
#include <algorithm>
#include <cmath>
#include <iostream>

Health::Health(float maxHealth): maxHealth(maxHealth), currentHealth(maxHealth) {
}
float Health::updateHealth(float delta) {
    if (!alive)
        return 0.f;
    
    int updatedHealth = currentHealth + delta;
    currentHealth = std::fmax(0, std::fmin(maxHealth, updatedHealth));
    std::cout << currentHealth << "/" << maxHealth << '\n';
    alive = currentHealth > 0.f;
    return getHealthRacio();
}

float Health::getCurrentHealth() {
    return currentHealth;
}
float Health::getMaxHealth() {
    return maxHealth;
}
float Health::getHealthRacio() {
    return currentHealth / maxHealth;
}
bool Health::isAlive() {
    return currentHealth > 0.f;
}
