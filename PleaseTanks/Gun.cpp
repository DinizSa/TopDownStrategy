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
        bool collided = !projectile->applyVelocity();
        if (collided) {
            Projectile* explosion = projectile->onHit();
            delete projectile;
            projectiles.erase(it);
            explosion->onHit();
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
    
    Sprite sp = Sprite({SpriteNames::effects, 10, 19, 80, true});
    Projectile* projectile = new Projectile(size, pos, currentRotation, collisionMaskId, sp);
    projectiles.emplace_back(projectile);
}
