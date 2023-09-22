//
//  Hull.cpp
//  PleaseTanks
//
//  Created by Diniz Sá on 14/09/2023.
//

#include "Hull.hpp"

Hull::Hull(sf::Vector2f imageSize, int spriteIndex) :
    PhysicsBody({imageSize.x * (6.f/10.f), imageSize.y}),
    Drawable(imageSize, PhysicsBody::centerWorld, PhysicsBody::rotation, 2.f, SpriteNames::hulls, spriteIndex)
{
    setMovementCollisions(true);
}
