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
}

FireExplosion::FireExplosion(sf::Vector2f position, int collisionMaskId):
    Explosion({100.f, 100.f}, {50.f, 50.f}, position, collisionMaskId, {SpriteNames::effects, 21, 28, 80, false}, 30)
{
    std::vector<PhysicsBody*> collided = getCollided();
    
    for (auto body : collided) {
        body->receiveDamage(damage);
    }
    
    sf::Sound* sound = AssetManager::get()->playSound(SoundNames::metalExplosion, audioPlayerId);
    sound->setLoop(false);
}
