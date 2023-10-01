//
//  Projectile.cpp
//  PleaseTanks
//
//  Created by Diniz Sá on 20/09/2023.
//

#include "Explosion.hpp"
#include "Utils.hpp"
#include "AutoSprite.hpp"
#include "CombatUnit.hpp"

Explosion::Explosion(sf::Vector2f size, sf::Vector2f physicsBodySize, sf::Vector2f position, int maskId, Sprite sprite, int damage):
    PhysicsBody(physicsBodySize), AutoSprite(size, 4.f, sprite),
    damage(damage)
{
    setMovementCollisions(false);
    setCollisionMaskId(maskId);
    translate(position, false);
    
    setPosition(position, 0.f);
    setPosition(&centerWorld, &rotation);
}
Explosion::~Explosion() {
}

FireExplosion::FireExplosion(sf::Vector2f size, sf::Vector2f position, int collisionMaskId):
    Explosion(size, size/2.f, position, collisionMaskId, {SpriteNames::effects, 21, 28, 80, false, [&](){dirty = true;}}, 30)
{
    sf::Sound* sound = AssetManager::get()->playSound(SoundNames::shellExplosion, audioPlayerId);
    sound->setLoop(false);
    
    std::vector<PhysicsBody*> collided = getCollided();
    for (auto body : collided) {
        CombatUnit* combatUnit = dynamic_cast<CombatUnit*>(body);
        if (combatUnit != nullptr) {
            combatUnit->receiveDamage(damage);
        }
    }
}
LaunchExplosion::LaunchExplosion(sf::Vector2f size, sf::Vector2f position):
    Explosion(size, {0.f, 0.f}, position, collisionMaskId, {SpriteNames::shotEffect, 0, 5, 80, false, [&](){dirty = true;}}, 0)
{}
