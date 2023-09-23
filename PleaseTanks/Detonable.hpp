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

class Detonable : public PhysicsBody, public AutoSprite {
protected:
    static std::vector<Detonable*> detonables;
    static void addDetonable(Detonable* detonable);
    static void removeDetonable(Detonable* detonable);
public:
    static void updateDetonables();
    
protected:
    float velocityScalar;
    bool destroyed;
public:
    Detonable(sf::Vector2f size, sf::Vector2f physicsBodySize, sf::Vector2f position, float angleDegrees, int collisionMaskId, Sprite sprite, float velocityScalar);
    virtual ~Detonable();
    virtual void updateDetonable() {};
    bool isDestroyed();
};

class FireProjectile : public Detonable {
public:
    FireProjectile(sf::Vector2f position, float angleDegrees, int collisionMaskId);
    ~FireProjectile();
    void updateDetonable() override;
};

class FireExplosion : public Detonable {
public:
    FireExplosion(sf::Vector2f position, int collisionMaskId);
};
