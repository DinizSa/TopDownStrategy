//
//  Projectile.cpp
//  PleaseTanks
//
//  Created by Diniz Sá on 20/09/2023.
//

#include "Projectile.hpp"
#include "Utils.hpp"
#include "Explosion.hpp"

Projectile::Projectile(sf::Vector2f size, sf::Vector2f position, float angleDegrees, int maskId) :
    PhysicsBody(size/100.f),
    Drawable(size, PhysicsBody::centerWorld, PhysicsBody::rotation, SpriteNames::effects, 11),
    velocityScalar(10.f)
{
    setCollisionMaskId(maskId);
    translate(position, false);
    setSpriteRange(10, 19);
    setAutomaticSprite(50, true);
    
    
    sf::Vector2f velocity = Utils::getVector(angleDegrees, velocityScalar);
    setVelocity(velocity);
    float imageInitialAngle = 90.f;
    
    
    float angle = imageInitialAngle + Utils::getAngle(velocity);
    setMovementCollisions(true);
    rotate(angle);
}

Explosion* Projectile::onHit() {
    Explosion* explosion = new Explosion({200.f, 200.f}, centerWorld(), 21, 28);
    return explosion;
}
