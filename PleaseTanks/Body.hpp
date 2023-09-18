//
//  Hull.hpp
//  PleaseTanks
//
//  Created by Diniz Sá on 14/09/2023.
//

#pragma once
#include "Drawable.hpp"
#include "PhysicsBody.hpp"

class Body : public PhysicsBody, public Drawable {
public:
    Body(sf::Vector2f size, const std::string&& texturePath);
};
