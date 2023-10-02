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

class Projectile : public PhysicsBody, public AutoSprite, protected AudioPlayer {
protected:
    float range;
    float velocityScalar;
public:
    Projectile(sf::Vector2f size, sf::Vector2f physicsBodySize, sf::Vector2f position, float angleDegrees, int collisionMaskId, Sprite sprite, float velocityScalar, float range, float zIndex);
    virtual ~Projectile();
    virtual void update() override;
    virtual void onHit() = 0;
};

class FireProjectile : public Projectile {
public:
    FireProjectile(sf::Vector2f position, float angleDegrees, int collisionMaskId);
    void onHit() override;
};

class BulletProjectile : public Projectile {
public:
    BulletProjectile(sf::Vector2f position, float angleDegrees, int collisionMaskId);
    void onHit() override;
};

class GrenadeProjectile : public Projectile {
private:
    float secondsToExplosion;
public:
    GrenadeProjectile(sf::Vector2f position, float angleDegrees, int collisionMaskId);
    void onHit() override;
    void update() override;
};
