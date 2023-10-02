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

Projectile::Projectile(sf::Vector2f size, sf::Vector2f physicsBodySize, sf::Vector2f position, float angleDegrees, int maskId, Sprite sprite, float velocityScalar, float range, float zIndex):
    PhysicsBody(physicsBodySize),
    AutoSprite(size, zIndex, sprite),
    velocityScalar(velocityScalar), range(range)
{
    setPosition(&centerWorld, &rotation);
    setCollisionMaskId(maskId);
    
    translate(position, false);
    sf::Vector2f velocity = Utils::getVector(angleDegrees, velocityScalar);
    setVelocityAndRotate(velocity);
}
Projectile::~Projectile() {
}
void Projectile::update() {
    PhysicsBody::update();
    
    if (getTraveledDistance() > range) {
        expired = true;
        return;
    }
    
    bool collided = collidedAny();
    if (collided) {
        this->onHit();
    }
}

FireProjectile::FireProjectile(sf::Vector2f position, float angleDegrees, int collisionMaskId):
    Projectile({100.f, 100.f}, {5.f, 5.f}, position, angleDegrees, collisionMaskId, {SpriteNames::effects, 10, 19, 80, true}, 10.f, 500.f, 4.f)
{
    sf::Sound* sound = AssetManager::get()->playSound(SoundNames::tankGunBlast, audioPlayerId);
    sound->setLoop(false);
    sound->setVolume(20.f);
}

void FireProjectile::onHit() {
    new FireExplosion({100.f, 100.f}, centerWorld(), collisionMaskId);
    expired = true;
}


BulletProjectile::BulletProjectile(sf::Vector2f position, float angleDegrees, int collisionMaskId):
    Projectile({50.f, 50.f}, {5.f, 5.f}, position, angleDegrees, collisionMaskId, {SpriteNames::effects2, 14, 14, 0, false}, 10.f, 500.f, 2.f)
{
    sf::Sound* sound = AssetManager::get()->playSound(SoundNames::rifle, audioPlayerId);
    sound->setLoop(false);
    sound->setVolume(20.f);
}

void BulletProjectile::onHit() {
    sf::Sound* sound = AssetManager::get()->playSound(SoundNames::bulletHitMetal, audioPlayerId);
    sound->setLoop(false);
    sound->setVolume(50.f);
    
    new BulletExplosion({100.f, 100.f}, centerWorld(), collisionMaskId);
    expired = true;
}

GrenadeProjectile::GrenadeProjectile(sf::Vector2f position, float angleDegrees, int collisionMaskId):
    Projectile({20.f, 20.f}, {05.f, 10.f}, position, angleDegrees, collisionMaskId, {SpriteNames::grenade, 0, 0, 0, false}, 2.f, 100.f, 1.f), secondsToExplosion(5.f)
{}

void GrenadeProjectile::onHit() {
    sf::Sound* sound = AssetManager::get()->playSound(SoundNames::grenadeExplosion, audioPlayerId);
    sound->setLoop(false);
    sound->setVolume(60.f);
    
    new FireExplosion({100.f, 100.f}, centerWorld(), collisionMaskId);
    expired = true;
}
void GrenadeProjectile::update() {
    PhysicsBody::update();
    
    if (getTraveledDistance() > range) {
        setVelocity({0.f, 0.f});
    }
    rotate(0.4f);
    
    secondsToExplosion -= 1/60.f;
    if (secondsToExplosion <= 0) {
        onHit();
    }
}
