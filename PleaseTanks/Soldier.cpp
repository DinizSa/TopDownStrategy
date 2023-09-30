//
//  Soldier.cpp
//  PleaseTanks
//
//  Created by Diniz Sá on 30/09/2023.
//

#include "Soldier.hpp"

Soldier::Soldier(sf::Vector2f size, sf::Vector2f position): PhysicsBody(size/2.f), feet(size/1.5f, 1, Sprite(SpriteNames::soldierFeet, 0, 19, 0, false)), body(size, 2, Sprite(SpriteNames::soldierSprite, 7, 48, 0, false)) {
    feet.setPosition(&centerWorld, &rotation);
    body.setPosition(&centerWorld, &rotation);
    translate(position, false);
    
    int id = PhysicsBody::getAndIncrementMaskId();
    setCollisionMaskId(id);
    
    PhysicsBody::addUpdatable(this);
    
    setMovementCollisions(true);
}

Soldier::~Soldier() {
    PhysicsBody::removeUpdatable(this);
}

void Soldier::update() {
    setPathVelocity(1.f);
    applyVelocity();
}
