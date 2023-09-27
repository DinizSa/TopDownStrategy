//
//  Projectile.cpp
//  PleaseTanks
//
//  Created by Diniz Sá on 20/09/2023.
//

#include "Mine.hpp"
#include "Utils.hpp"
#include "Drawable.hpp"
#include "Explosion.hpp"

Mine::Mine(sf::Vector2f position):
    PhysicsBody({20.f, 20.f})
{
    translate(position, false);
    
    PhysicsBody::addPhysicsBody(this);
}
Mine::~Mine() {
    PhysicsBody::removePhysicsBody(this);
}
void Mine::update() {
    bool collided = collidedAny();
    if (collided) {
        new FireExplosion(centerWorld(), collisionMaskId);
        expired = true;
    }
}

BasicMine::BasicMine(sf::Vector2f position): Mine(position) {
    Drawable* mine = new Drawable({40.f, 40.f}, 0.f, SpriteNames::mine, 0);
    mine->setPosition(position, 0.f);
}
