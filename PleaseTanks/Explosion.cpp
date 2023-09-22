//
//  Explosion.cpp
//  PleaseTanks
//
//  Created by Diniz Sá on 20/09/2023.
//

#include "Explosion.hpp"

Explosion::Explosion(sf::Vector2f size, sf::Vector2f position, int startSprite, int endSprite) :
    PhysicsBody(size / 4.f),
    Drawable(size, PhysicsBody::centerWorld, PhysicsBody::rotation, SpriteNames::effects, 24)
{
    translate(position, false);
    setSpriteRange(startSprite, endSprite);
    setAutomaticSprite(100, false);
}

void Explosion::applyHit() {
    auto collided = getCollided();
    std::cout << "collided: " << collided.size() << std::endl;
}
