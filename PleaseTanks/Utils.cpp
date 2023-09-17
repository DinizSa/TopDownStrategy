//
//  Utils.cpp
//  PleaseTanks
//
//  Created by Diniz Sá on 17/09/2023.
//

#include "Utils.hpp"
#include <cmath>

float Utils::getDistance(const sf::Vector2<float>& a, const sf::Vector2<float>& b) {
    return getLength(b.x - a.x, b.y - a.y);
}
float Utils::getLength(float x, float y) {
    return sqrt(pow(x, 2) + pow(y, 2));
}
