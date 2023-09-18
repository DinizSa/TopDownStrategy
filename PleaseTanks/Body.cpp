//
//  Hull.cpp
//  PleaseTanks
//
//  Created by Diniz Sá on 14/09/2023.
//

#include "Body.hpp"

Body::Body(sf::Vector2f size, const std::string&& texturePath) :
    PhysicsBody(size),
    Drawable(size, PhysicsBody::centerWorld, PhysicsBody::rotation, std::move(texturePath))
{}
