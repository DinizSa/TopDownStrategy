//
//  Explosion.cpp
//  PleaseTanks
//
//  Created by Diniz Sá on 20/09/2023.
//

#include "Explosion.hpp"

Explosion::Explosion(sf::Vector2f size, sf::Vector2f position) :
    PhysicsBody(size),
    Drawable(size, PhysicsBody::centerWorld, PhysicsBody::rotation, SpriteNames::effects, 24)
{
    translate(position);
    setSpriteRange(24, 30);
    setAutomaticSprite(60, false);
}