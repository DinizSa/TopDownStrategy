//
//  Hull.hpp
//  PleaseTanks
//
//  Created by Diniz Sá on 14/09/2023.
//

#pragma once
#include "Drawable.hpp"
#include "PhysicsBody.hpp"

class Hull : public PhysicsBody, public Drawable {
public:
    Hull(sf::Vector2f size, int spriteIndex);
};
