//
//  Projectile.cpp
//  PleaseTanks
//
//  Created by Diniz Sá on 20/09/2023.
//

#include "Explosion.hpp"
#include "Utils.hpp"
#include "AutoSprite.hpp"

Explosion::Explosion(sf::Vector2f size, sf::Vector2f physicsBodySize, sf::Vector2f position, int maskId, Sprite sprite):
    PhysicsBody(physicsBodySize),
    AutoSprite(size, PhysicsBody::centerWorld, PhysicsBody::rotation, 4.f, sprite)
{
    setCollisionMaskId(maskId);
    translate(position, false);
    setMovementCollisions(true);
}

FireExplosion::FireExplosion(sf::Vector2f position, int collisionMaskId):
    Explosion({200.f, 200.f}, {50.f, 50.f}, position, collisionMaskId, {SpriteNames::effects, 21, 28, 80, false})
{
    auto collided = getCollided();
    std::cout << "collided: " << collided.size() << '\n';
}

