//
//  Projectile.cpp
//  PleaseTanks
//
//  Created by Diniz Sá on 20/09/2023.
//

#include "Explosion.hpp"
#include "Utils.hpp"
#include "AutoSprite.hpp"
#include "Health.hpp"
#include "Hull.hpp"

Explosion::Explosion(sf::Vector2f size, sf::Vector2f physicsBodySize, sf::Vector2f position, int maskId, Sprite sprite, int damage):
    PhysicsBody(physicsBodySize),
    AutoSprite(size, 4.f, sprite),
    damage(damage)
{
    setPosition(&centerWorld, &rotation);
    setCollisionMaskId(maskId);
    translate(position, false);
    setMovementCollisions(true);
}

FireExplosion::FireExplosion(sf::Vector2f position, int collisionMaskId):
    Explosion({200.f, 200.f}, {50.f, 50.f}, position, collisionMaskId, {SpriteNames::effects, 21, 28, 80, false}, 30)
{
    std::vector<PhysicsBody*> collided = getCollided();
    std::cout << "collided: " << collided.size() << '\n';
    
    for (auto body : collided) {
        body->receiveDamage(damage);
    }
}
