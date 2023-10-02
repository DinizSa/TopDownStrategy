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
void Health::updateHealth(float delta) {
    int updatedHealth = currentHealth + delta;
    currentHealth = std::fmax(0, std::fmin(maxHealth, updatedHealth));
    std::cout << currentHealth << "/" << maxHealth << '\n';
}

float Health::getCurrentHealth() {
    return currentHealth;
}
float Health::getMaxHealth() {
    return maxHealth;
}
