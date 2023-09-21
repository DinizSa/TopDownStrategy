//
//  Hull.cpp
//  PleaseTanks
//
//  Created by Diniz Sá on 14/09/2023.
//

#include "Gun.hpp"

Gun::Gun(sf::Vector2f imageSize, int spriteIndex) :
    PhysicsBody({imageSize.x*(3.f/10.f), imageSize.y*(6.f/10.f)}),
    Drawable(imageSize, PhysicsBody::centerWorld, PhysicsBody::rotation, SpriteNames::guns, spriteIndex),
    angularSpeed(5.f)
{
    translate({0.f, imageSize.y * (0.f/10.f)});
    setLocalRotationCenter({0.f, imageSize.y * (1.5f/10.f)});
}

float Gun::getAngularSpeed() {
    return angularSpeed;
}
