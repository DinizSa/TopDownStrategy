//
//  Projectile.hpp
//  PleaseTanks
//
//  Created by Diniz Sá on 20/09/2023.
//

#pragma once

#include <vector>

#include "PhysicsBody.hpp"
#include "AutoSprite.hpp"
#include "AudioPlayer.hpp"
#include "Weapon.hpp"

class Projectile : public PhysicsBody, public AutoSprite, protected AudioPlayer {
protected:
    std::shared_ptr<Weapon> weapon;
    float timerSeconds, timeCollision;
    bool shouldDetonate, canCollide;
    float range;
public:
    Projectile(sf::Vector2f position, float angleDegrees, int collisionMaskId, const std::shared_ptr<Weapon> weapon, float forcePercentage = 100.f);
    virtual ~Projectile();
    virtual void update() override;
};

//class FireProjectile : public Projectile {
//public:
//    FireProjectile(sf::Vector2f position, float angleDegrees, int collisionMaskId);
//    void onHit() override;
//};
//
//class BulletProjectile : public Projectile {
//public:
//    BulletProjectile(sf::Vector2f position, float angleDegrees, int collisionMaskId);
//    void onHit() override;
//};
//
//class GrenadeProjectile : public Projectile {
//private:
//    float secondsToExplosion;
//public:
//    GrenadeProjectile(sf::Vector2f position, float angleDegrees, int collisionMaskId, const Weapon& weapon);
//    void onHit() override;
//    void update() override;
//};
