//
//  Hull.cpp
//  PleaseTanks
//
//  Created by Diniz Sá on 14/09/2023.
//

#include "Gun.hpp"

Gun::Gun(sf::Vector2<float> size, sf::Vector2<float> position) : Body(size, position, "/Users/Shared/merda/PleaseTanks/images/Gun_01.png"), angularSpeed(5.f)
{
    setDeltaCenter({0.f, size.y*(-1.f/10.f)});
    setRotationCenter({size.x/2, size.y*(6.5f/10.f)});
}

float Gun::getAngularSpeed() {
    return angularSpeed;
}
void Gun::rotate(float deltaAngle) {
    Body::rotate(deltaAngle);
}
void Gun::rotateAroundParent(float currentAngle, float degrees) {
    Body::rotateAroundParent(currentAngle, degrees);
}
