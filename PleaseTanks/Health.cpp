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

Health::Health(float maxHealth, float armour): maxHealth(maxHealth), currentHealth(maxHealth), armour(armour), alive(true) {
}
float Health::receiveDamage(float damage, float armourPenetration) {
    if (!alive)
        return 0.f;

    float mitigatedDamage = damage * (1 - ((std::fmax(armour - armourPenetration, 0.f))/100));
    float updatedHealth = float((int)((currentHealth - mitigatedDamage) * 100)/100);
    currentHealth = std::fmax(0, std::fmin(maxHealth, updatedHealth));
    std::cout << currentHealth << "/" << maxHealth << '\n';
    alive = currentHealth > 0.f;
    return getHealthRacio();
}

float Health::getCurrentHealth() const {
    return currentHealth;
}
float Health::getMaxHealth() const {
    return maxHealth;
}
float Health::getHealthRacio() const {
    return currentHealth / maxHealth;
}
bool Health::isAlive() const {
    return currentHealth > 0.f;
}
