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
    Drawable(imageSize, PhysicsBody::centerWorld, PhysicsBody::rotation, 3.f, SpriteNames::guns, spriteIndex),
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
    for (auto it = projectiles.begin(); it != projectiles.end(); ) {
        Projectile* projectile = *it;
        bool hit = !projectile->applyVelocity();
        if (hit) {
            Explosion* explosion = projectile->onHit();
            explosions.push_back(explosion);
            delete projectile;
            projectiles.erase(it);
            explosion->applyHit();
        } else {
            ++it;
        }
    }
    for (auto it = explosions.begin(); it != explosions.end(); ) {
        Explosion* explosion = *it;
        bool isDirty = explosion->isDirty();
        if (isDirty) {
            explosions.erase(it);
        } else {
            ++it;
        }
    }
}

void Gun::shot() {
    float currentRotation = PhysicsBody::rotation();
    
    sf::Vector2f size = {150.f, 150.f};
    
    float radius = body.width > body.height ? body.width : body.height;
    sf::Vector2f deltaPos = Utils::getVector(currentRotation, radius);
    sf::Vector2f pos = centerWorld() + deltaPos;
    
    Projectile* projectile = new Projectile(size, pos, currentRotation, collisionMaskId);
    projectiles.emplace_back(projectile);
}
