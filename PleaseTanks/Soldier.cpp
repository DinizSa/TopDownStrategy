//
//  Soldier.cpp
//  PleaseTanks
//
//  Created by Diniz Sá on 30/09/2023.
//

#include "Soldier.hpp"

Soldier::Soldier(sf::Vector2f size, sf::Vector2f position): PhysicsBody(size/2.f), feet(size/1.5f, 1, Sprite(SpriteNames::soldierFeet, 8, 8, 0, false)), body(size, 2, Sprite(SpriteNames::soldierMove, 0, 19, 80, true)) {

    feet.setPosition(&centerWorld, &rotation);
    body.setPosition(&centerWorld, &rotation);
    translate(position, false);

    setSpeed(1.0);
    setAngularSpeed(1.f);
    
    int id = PhysicsBody::getAndIncrementMaskId();
    setCollisionMaskId(id);
    
    PhysicsBody::addUpdatable(this);
    
    setMovementCollisions(true);
    
    moving.subscribe(this, [&](bool isMoving) {
        std::cout << "moving: " << isMoving << std::endl;
        if (isMoving) {
            feet.updateSprite(Sprite(SpriteNames::soldierFeet, 0, 19, 80, true));
        } else {
            feet.updateSprite(Sprite(SpriteNames::soldierFeet, 8, 8, 0, false));
        }
    });
    
}
Soldier::~Soldier() {
    PhysicsBody::removeUpdatable(this);
}
void Soldier::attack() {
//    body.updateSprite(Sprite(SpriteNames::soldierReload, 0, 19, 80, false));
    body.updateSprite(Sprite(SpriteNames::soldierShoot, 0, 2, 100, false));
    body.setEndCallback([&](){
        std::cout << "animation finished" << std::endl;
        body.updateSprite(Sprite(SpriteNames::soldierReload, 0, 19, 80, false));
        body.setEndCallback([&]() {
            std::cout << "animation 2 finished" << std::endl;
            body.updateSprite(Sprite(SpriteNames::soldierMove, 0, 19, 80, true));
            body.setEndCallback([](){});
        });
    });
}
