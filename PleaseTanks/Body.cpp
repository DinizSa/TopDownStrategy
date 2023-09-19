//
//  Hull.cpp
//  PleaseTanks
//
//  Created by Diniz Sá on 14/09/2023.
//

#include "Body.hpp"

Body::Body(sf::Vector2f imageSize, sf::Vector2f physicsBodySize, SpriteNames sprite, int spriteIndex) :
    PhysicsBody(physicsBodySize),
    Drawable(imageSize, PhysicsBody::centerWorld, PhysicsBody::rotation, sprite, spriteIndex)
{}
