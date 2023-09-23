//
//  Projectile.cpp
//  PleaseTanks
//
//  Created by Diniz Sá on 20/09/2023.
//

#include "Projectile.hpp"
#include "Utils.hpp"
#include "AutoSprite.hpp"

Projectile::Projectile(sf::Vector2f size, sf::Vector2f position, float angleDegrees, int maskId, Sprite sprite) :
    PhysicsBody(size/100.f),
    AutoSprite(size, PhysicsBody::centerWorld, PhysicsBody::rotation, 4.f, sprite),
    velocityScalar(10.f)
{
    setCollisionMaskId(maskId);
    translate(position, false);
    
    sf::Vector2f velocity = Utils::getVector(angleDegrees, velocityScalar);
    setVelocityAndRotate(velocity);

    setMovementCollisions(true);
}

Projectile* Projectile::onHit() {
    Sprite sp = Sprite({SpriteNames::effects, 21, 28, 80, false});
    Projectile* projectile = new Projectile({200.f, 200.f}, centerWorld(), 0.f, collisionMaskId, sp);
    return projectile;
}
