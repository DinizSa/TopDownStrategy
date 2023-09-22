//
//  Hull.cpp
//  PleaseTanks
//
//  Created by Diniz Sá on 14/09/2023.
//

#include "Gun.hpp"
#include "Utils.hpp"

Gun::Gun(sf::Vector2f imageSize, int spriteIndex) :
    PhysicsBody({imageSize.x*(3.f/10.f), imageSize.y*(6.f/10.f)}),
    Drawable(imageSize, PhysicsBody::centerWorld, PhysicsBody::rotation, SpriteNames::guns, spriteIndex),
    angularSpeed(5.f)
{
    setLocalRotationCenter({0.f, imageSize.y * (1.5f/10.f)});
}
Gun::~Gun() {
    for (auto projectile : projectiles) {
        delete projectile;
    }
}
float Gun::getAngularSpeed() {
    return angularSpeed;
}

void Gun::update() {
    for (auto projectile : projectiles) {
        projectile->applyVelocity();
    }
}

void Gun::shot() {
    float currentRotation = PhysicsBody::rotation();
    
    sf::Vector2f size = {100.f, 100.f};
    
    float radius = body.width > body.height ? body.width : body.height;
    sf::Vector2f deltaPos = Utils::getVector(currentRotation, radius);
    sf::Vector2f pos = centerWorld() + deltaPos;
    
    float velocityScalar = 8;
    sf::Vector2f velocity = Utils::getVector(currentRotation, velocityScalar);
    
    Projectile* projectile = new Projectile(size, pos, velocity);
    projectiles.emplace_back(projectile);
}

void Gun::draw(sf::RenderWindow& window) {
    Drawable::draw(window);
    for (auto projectile : projectiles) {
        projectile->draw(window);
    }
}
