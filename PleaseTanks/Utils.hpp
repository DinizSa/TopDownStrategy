//
//  Utils.hpp
//  PleaseTanks
//
//  Created by Diniz Sá on 17/09/2023.
//
#include <SFML/Graphics.hpp>
#pragma once

class Utils {
public:
    static float getDistance(const sf::Vector2<float>& a, const sf::Vector2<float>& b);
    static float getLength(float x, float y);
};
