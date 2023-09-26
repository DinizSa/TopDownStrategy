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

Health::Health(int maxHealth): maxHealth(maxHealth), currentHealth(maxHealth) {
}
void Health::updateHealth(int delta) {
    int updatedHealth = currentHealth + delta;
    currentHealth = std::max(0, std::min(maxHealth, updatedHealth));
    std::cout << currentHealth << "/" << maxHealth << '\n';
}
void Health::updateHealth(float delta) {
    int dHealth = round(delta);
    updateHealth(dHealth);
}
