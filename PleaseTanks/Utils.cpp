//
//  Utils.cpp
//  PleaseTanks
//
//  Created by Diniz Sá on 17/09/2023.
//

#include "Utils.hpp"
#include <cmath>

float Utils::getDistance(const sf::Vector2f& a, const sf::Vector2f& b) {
    return getLength(b.x - a.x, b.y - a.y);
}
float Utils::getLength(float x, float y) {
    return sqrt(pow(x, 2) + pow(y, 2));
}
float Utils::getLength(const sf::Vector2f& v) {
    return sqrt(pow(v.x, 2) + pow(v.y, 2));
}
float Utils::getAngle(const sf::Vector2f& v) {
    float length = Utils::getLength(v);
    auto ang = (acos(v.x / length)) * 180 / M_PI;
    bool firstSecondQuadrant = v.y >= 0.f;
    return firstSecondQuadrant ? ang : -ang;
}
sf::Vector2f Utils::getVector(float rotationDegrees, float hypotenusa) {
    float rotRadians = Utils::getRadians(rotationDegrees);
    return sf::Vector2f({hypotenusa * sin(rotRadians), -hypotenusa * cos(rotRadians)});
}

float Utils::getDegrees(float radians) {
    return radians * 180 / M_PI;
}
float Utils::getRadians(float degrees) {
    return degrees * M_PI / 180;
}
