//
//  Hull.cpp
//  PleaseTanks
//
//  Created by Diniz Sá on 14/09/2023.
//

#include "Gun.hpp"
#include "Utils.hpp"
#include "Projectile.hpp"

Gun::Gun(sf::Vector2f imageSize, int spriteIndex) :
    PhysicsBody({imageSize.x*(3.f/10.f), imageSize.y*(6.f/10.f)}),
    Drawable(imageSize, PhysicsBody::centerWorld, PhysicsBody::rotation, 3.f, SpriteNames::guns, spriteIndex),
    angularSpeed(5.f)
{
    setLocalRotationCenter({0.f, imageSize.y * (1.5f/10.f)});
}
float Gun::getAngularSpeed() {
    return angularSpeed;
}

void Gun::shot() {
    float currentRotation = PhysicsBody::rotation();
    
    float radius = body.width > body.height ? body.width : body.height;
    sf::Vector2f deltaPos = Utils::getVector(currentRotation, radius);
    sf::Vector2f pos = centerWorld() + deltaPos;
    
    new FireProjectile(pos, currentRotation, collisionMaskId);
}
