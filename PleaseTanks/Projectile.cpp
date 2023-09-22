//
//  Projectile.cpp
//  PleaseTanks
//
//  Created by Diniz Sá on 20/09/2023.
//

#include "Projectile.hpp"
#include "Utils.hpp"

Projectile::Projectile(sf::Vector2f size, sf::Vector2f position, sf::Vector2f velocity) :
    PhysicsBody(size),
    Drawable(size, PhysicsBody::centerWorld, PhysicsBody::rotation, SpriteNames::effects, 11)
{
    translate(position, false);
    setSpriteRange(10, 19);
    setAutomaticSprite(50, true);
    setVelocity(velocity);
    float imageInitialAngle = 90.f;
    float angle = imageInitialAngle + Utils::getAngle(velocity);
    rotate(angle);
    rect.scale(2.f, 2.f);
}
