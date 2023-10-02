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
    
    if (weapon->launchSound != nullptr)
        AssetManager::get()->playSound(*weapon->launchSound, audioPlayerId);
}
Projectile::~Projectile() {
}
void Projectile::update() {
    PhysicsBody::update();
    
    timerSeconds += 1/CONFIGS::FPS;
    
    if (weapon->rotation > 0.f)
        rotate(weapon->rotation);
    
//  range detonation
    if (getTraveledDistance() > weapon->range) {
        if (weapon->loseForceOnMaxRange) {
            expired = true;
            return;
        }
        if (weapon->explodeOnMaxRange)
            shouldDetonate = true;
        setVelocity({0.f, 0.f});
    }
    
//  self detonation
    if (weapon->selfDetonationSeconds > -1 && timerSeconds > weapon->selfDetonationSeconds) {
        shouldDetonate = true;
    }
    
//  collision detonation
    if (weapon->collisionDetonationSeconds > -1 && timeCollision == -1) {
        if (collidedAny())
            timeCollision = timerSeconds;
    }
    if (timeCollision >= timerSeconds + weapon->collisionDetonationSeconds) {
        shouldDetonate = true;
    }
    
    if (shouldDetonate) {
        if (weapon->explosionSound != nullptr)
            AssetManager::get()->playSound(*weapon->explosionSound, audioPlayerId);
        
        new Explosion(centerWorld(), collisionMaskId, weapon);
        
        expired = true;
        return;
    }
}
