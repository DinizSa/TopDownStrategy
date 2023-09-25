//
//  Hull.cpp
//  PleaseTanks
//
//  Created by Diniz Sá on 14/09/2023.
//

#include "Hull.hpp"
#include "Utils.hpp"

Hull::Hull(sf::Vector2f imageSize, int spriteIndex) :
    PhysicsBody({imageSize.x * (6.f/10.f), imageSize.y}),
    Drawable(imageSize, 2.f, SpriteNames::hulls, spriteIndex)
{
    setMovementCollisions(true);
    
    setPosition(&centerWorld, &rotation);
    
    exhaust = new AutoSprite({{100.f, 100.f}, 2.f, {SpriteNames::effects, 0, 2, 90, true}});
    exhaust->setPosition(&exhaustPosition, &rotation);
    
    PhysicsBody::centerWorld.subscribe(exhaust, [&](sf::Vector2f center) {
        float currentRotation = PhysicsBody::rotation();
        float radius = (body.height / 2.f) - 5;
        sf::Vector2f deltaPos = Utils::getVector(currentRotation, radius);
        exhaustPosition = center - deltaPos;
        exhaustPosition.notify();
    });
}

Hull::~Hull() {
    delete exhaust;
}
