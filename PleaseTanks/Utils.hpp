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
    static float getDistance(const sf::Vector2f& a, const sf::Vector2f& b);
    static float getLength(float x, float y);
    static float getLength(const sf::Vector2f& v);
};
