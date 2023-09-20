//
//  Explosion.hpp
//  PleaseTanks
//
//  Created by Diniz Sá on 20/09/2023.
//

#pragma once
#include "Drawable.hpp"
#include "PhysicsBody.hpp"

class Explosion : public PhysicsBody, public Drawable {
public:
    Explosion(sf::Vector2f size, sf::Vector2f position);
};
