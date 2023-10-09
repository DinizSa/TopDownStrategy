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

Projectile::Projectile(sf::Vector2f position, float angleDegrees, int maskId, const std::shared_ptr<Weapon> weapon, float forcePercentage):
    PhysicsBody(weapon->projectilePhysicsSize),
    AutoSprite(weapon->projectileImageSize, weapon->zIndex, *weapon->missileSprite), timerSeconds(0.f), timeCollision(-1.f),
weapon(weapon), shouldDetonate(false), canCollide(!weapon->isDraggable)
{
    setPosition(&centerWorld, &rotation);
    setCollisionMaskId(maskId);
    
    float forceFactor = std::min(forcePercentage, 100.f) / 100.f;
    range = weapon->range * forceFactor;
    
    translate(position, false);
    if (weapon->velocityScalar > 0.f) {
        float velocityScalar = weapon->velocityScalar * forceFactor;
        sf::Vector2f velocity = Utils::getVector(angleDegrees, velocityScalar);
        setVelocityAndRotate(velocity);
    }
    
    if (weapon->launchSound != nullptr)
        AssetManager::get()->playSound(*weapon->launchSound, audioPlayerId);
    
    if (weapon->launchSprite != nullptr) {
        auto launchEffect = new AutoSprite(weapon->lauchSize, weapon->zIndex, *weapon->launchSprite);
        launchEffect->setPosition(position, rotation());
    }
}
Projectile::~Projectile() {
}
void Projectile::update() {
    PhysicsBody::update();
    
    timerSeconds += 1/CONFIGS::FPS;
    
    if (weapon->rotation > 0.f)
        rotate(weapon->rotation);
    
    float traveledDistance = getTraveledDistance();
    if (weapon->isDraggable) {
        float scale = 2.f - fabs((range / 2) - traveledDistance) / (range / 2);
        rect.setScale(scale, scale);
    }
    
//  range detonation
    if (!canCollide && traveledDistance > range*(7/10.f)) {
        setColor(sf::Color::Red);
        canCollide = true;
    }
    if (traveledDistance > range) {
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
    if (canCollide && weapon->collisionDetonationSeconds > -1 && timeCollision == -1) {
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
