//
//  Projectile.cpp
//  PleaseTanks
//
//  Created by Diniz Sá on 20/09/2023.
//

#include "Projectile.hpp"
#include "Utils.hpp"
#include "AutoSprite.hpp"
#include "Explosion.hpp"

Projectile::Projectile(sf::Vector2f size, sf::Vector2f physicsBodySize, sf::Vector2f position, float angleDegrees, int maskId, Sprite sprite, float velocityScalar, float maxDistance):
    PhysicsBody(physicsBodySize),
    AutoSprite(size, 4.f, sprite),
    velocityScalar(velocityScalar), maxDistance(maxDistance)
{
    setPosition(&centerWorld, &rotation);
    setCollisionMaskId(maskId);
    
    translate(position, false);
    sf::Vector2f velocity = Utils::getVector(angleDegrees, velocityScalar);
    setVelocityAndRotate(velocity);
    
    PhysicsBody::addUpdatable(this);
}
Projectile::~Projectile() {
    PhysicsBody::removeUpdatable(this);
}
void Projectile::update() {
    if (getTraveledDistance() > maxDistance) {
        expired = true;
        return;
    }
    
    applyVelocity();
    bool collided = collidedAny();
    if (collided) {
        new FireExplosion(centerWorld(), collisionMaskId);
        expired = true;
    }
}

FireProjectile::FireProjectile(sf::Vector2f position, float angleDegrees, int collisionMaskId):
    Projectile({150.f, 150.f}, {5.f, 5.f}, position, angleDegrees, collisionMaskId, {SpriteNames::effects, 10, 19, 80, true}, 10.f, 500.f)
{
    sf::Sound* sound = AssetManager::get()->playSound(SoundNames::tankGunBlast, audioPlayerId);
    sound->setLoop(false);
    sound->setVolume(20.f);
}
