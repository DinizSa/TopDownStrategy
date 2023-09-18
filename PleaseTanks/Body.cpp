//
//  Hull.cpp
//  PleaseTanks
//
//  Created by Diniz Sá on 14/09/2023.
//

#include "Body.hpp"

Body::Body(sf::Vector2f imageSize, sf::Vector2f physicsBodySize, const std::string&& texturePath) :
    PhysicsBody(physicsBodySize),
    Drawable(imageSize, PhysicsBody::centerWorld, PhysicsBody::rotation, std::move(texturePath))
{}
