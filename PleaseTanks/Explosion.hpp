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

class Explosion : public PhysicsBody, public AutoSprite {
public:
    Explosion(sf::Vector2f size, sf::Vector2f physicsBodySize, sf::Vector2f position, int collisionMaskId, Sprite sprite);
};

class FireExplosion : public Explosion {
public:
    FireExplosion(sf::Vector2f position, int collisionMaskId);
};
