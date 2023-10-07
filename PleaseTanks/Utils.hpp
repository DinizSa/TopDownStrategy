//
//  Utils.hpp
//  PleaseTanks
//
//  Created by Diniz Sá on 17/09/2023.
//
#include <SFML/Graphics.hpp>
#include <vector>
#include "PhysicsBody.hpp"
#pragma once

class Utils {
public:
    static std::string floatToString(float value, int precision);
    static float getDistance(const sf::Vector2f& a, const sf::Vector2f& b);
    static float getLength(float x, float y);
    static float getLength(const sf::Vector2f& v);
    static float getAngle(const sf::Vector2f& vector);
    static sf::Vector2f getVector(float rotationDegrees, float hypotenusa);
    static float getDegrees(float radians);
    static float getRadians(float degrees);
    static std::vector<sf::Vector2f> getPathPoints(PhysicsBody* walker, sf::Vector2f destination);
};
