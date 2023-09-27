//
//  Projectile.cpp
//  PleaseTanks
//
//  Created by Diniz Sá on 20/09/2023.
//

#include "Mine.hpp"
#include "Utils.hpp"
#include "Explosion.hpp"

Mine::Mine(sf::Vector2f position, sf::Vector2f physicsSize):
    PhysicsBody({20.f, 20.f})
{
    translate(position, false);
    
    PhysicsBody::addUpdatable(this);
}
Mine::~Mine() {
    PhysicsBody::removeUpdatable(this);
}
void Mine::update() {
    bool collided = collidedAny();
    if (collided) {
        new FireExplosion(centerWorld(), collisionMaskId);
        expired = true;
        delete asset;
    }
}

BasicMine::BasicMine(sf::Vector2f position, sf::Vector2f size): Mine(position, size/2.f) {
    asset = new Drawable(size, 0.f, SpriteNames::mine, 0);
    asset->setPosition(position, 0.f);
}
