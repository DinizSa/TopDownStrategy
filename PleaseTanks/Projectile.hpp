//
//  Projectile.hpp
//  PleaseTanks
//
//  Created by Diniz Sá on 20/09/2023.
//

#pragma once
#include "Drawable.hpp"
#include "PhysicsBody.hpp"
#include "Explosion.hpp"

class Projectile : public PhysicsBody, public Drawable {
    float velocityScalar;
public:
    Projectile(sf::Vector2f size, sf::Vector2f position, float angleDegrees, int collisionMaskId);
    Explosion* onHit();
};
