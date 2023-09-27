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
    float velocityScalar;
public:
    Projectile(sf::Vector2f size, sf::Vector2f physicsBodySize, sf::Vector2f position, float angleDegrees, int collisionMaskId, Sprite sprite, float velocityScalar);
    virtual ~Projectile();
    void update() override;
};

class FireProjectile : public Projectile {
public:
    FireProjectile(sf::Vector2f position, float angleDegrees, int collisionMaskId);
};

class Mine : public Projectile {
public:
    Mine(sf::Vector2f position);
};
