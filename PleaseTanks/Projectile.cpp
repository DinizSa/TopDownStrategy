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
#include "Configs.hpp"

Projectile::Projectile(sf::Vector2f position, float angleDegrees, int maskId, const std::shared_ptr<Weapon> weapon):
    PhysicsBody(weapon->projectilePhysicsSize),
    AutoSprite(weapon->projectileImageSize, zIndex, *weapon->missileSprite), timerSeconds(0.f), timeCollision(-1.f),
    weapon(weapon)
{
    setPosition(&centerWorld, &rotation);
    setCollisionMaskId(maskId);
    
    translate(position, false);
    sf::Vector2f velocity = Utils::getVector(angleDegrees, weapon->velocityScalar);
    setVelocityAndRotate(velocity);
    
    sf::Sound* sound = AssetManager::get()->playSound(weapon->launchSound->name, audioPlayerId);
    sound->setLoop(weapon->launchSound->loop);
    sound->setVolume(weapon->launchSound->volume);
}
Projectile::~Projectile() {
}
void Projectile::update() {
    PhysicsBody::update();
    
    timerSeconds += 1/CONFIGS::FPS;
    
    if (weapon->rotation > 0.f) {
        rotate(weapon->rotation);
    }
    
//  range detonation
    if (getTraveledDistance() > weapon->range) {
        if (weapon->loseForceOnMaxRange) {
            expired = true;
            return;
        }
        if (weapon->explodeOnMaxRange) {
            shouldDetonate = true;
        }
        setVelocity({0.f, 0.f});
    }
    
//  self detonation
    if (weapon->selfDetonationSeconds > -1 && weapon->selfDetonationSeconds > timerSeconds) {
        shouldDetonate = true;
    }
    
//  collision detonation
    if (weapon->collisionDetonationSeconds > -1 && timeCollision == -1) {
        if (collidedAny()) {
            timeCollision = timerSeconds;
        }
    }
    if (timeCollision >= timerSeconds + weapon->collisionDetonationSeconds) {
        shouldDetonate = true;
    }
    
    if (shouldDetonate) {
        sf::Sound* sound = AssetManager::get()->playSound(weapon->explosionSound->name, audioPlayerId);
        sound->setLoop(weapon->explosionSound->loop);
        sound->setVolume(weapon->explosionSound->volume);
        
        new Explosion(centerWorld(), collisionMaskId, weapon);
        
        expired = true;
        return;
    }
}

//
//FireProjectile::FireProjectile(sf::Vector2f position, float angleDegrees, int collisionMaskId):
//    Projectile({100.f, 100.f}, {5.f, 5.f}, position, angleDegrees, collisionMaskId, {SpriteNames::effects, 10, 19, 80, true}, 10.f, 500.f, 4.f)
//{
//    sf::Sound* sound = AssetManager::get()->playSound(SoundNames::tankGunBlast, audioPlayerId);
//    sound->setLoop(false);
//    sound->setVolume(20.f);
//    
//    damage = 40;
//}
//
//void FireProjectile::onHit() {
//    new FireExplosion({100.f, 100.f}, centerWorld(), collisionMaskId, damage);
//    expired = true;
//}
//
//BulletProjectile::BulletProjectile(sf::Vector2f position, float angleDegrees, int collisionMaskId):
//    Projectile({50.f, 50.f}, {5.f, 5.f}, position, angleDegrees, collisionMaskId, {SpriteNames::effects2, 14, 14, 0, false}, 10.f, 500.f, 2.f)
//{
//    sf::Sound* sound = AssetManager::get()->playSound(SoundNames::rifle, audioPlayerId);
//    sound->setLoop(false);
//    sound->setVolume(20.f);
//    
//    damage = 20;
//}
//
//void BulletProjectile::onHit() {
//    sf::Sound* sound = AssetManager::get()->playSound(SoundNames::bulletHitMetal, audioPlayerId);
//    sound->setLoop(false);
//    sound->setVolume(50.f);
//    
//    new BulletExplosion({100.f, 100.f}, centerWorld(), collisionMaskId, damage);
//    expired = true;
//}
//
//GrenadeProjectile::GrenadeProjectile(sf::Vector2f position, float angleDegrees, int collisionMaskId, const Weapon& weapon):
//    Projectile({20.f, 20.f}, {05.f, 10.f}, position, angleDegrees, collisionMaskId, {SpriteNames::grenade, 0, 0, 0, false}, 2.f, weapon.range, 1.f), secondsToExplosion(5.f)
//{
//    damage = weapon.damage;
//}
//
//void GrenadeProjectile::onHit() {
//    sf::Sound* sound = AssetManager::get()->playSound(SoundNames::grenadeExplosion, audioPlayerId);
//    sound->setLoop(false);
//    sound->setVolume(60.f);
//    
//    new FireExplosion({100.f, 100.f}, centerWorld(), collisionMaskId, damage);
//    expired = true;
//}
//void GrenadeProjectile::update() {
//    PhysicsBody::update();
//    
//    if (getTraveledDistance() > range) {
//        setVelocity({0.f, 0.f});
//    }
//    rotate(0.4f);
//    
//    secondsToExplosion -= 1/CONFIGS::FPS;
//    if (secondsToExplosion <= 0) {
//        onHit();
//    }
//}
