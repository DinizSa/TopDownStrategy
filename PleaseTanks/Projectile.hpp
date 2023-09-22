//
//  Projectile.hpp
//  PleaseTanks
//
//  Created by Diniz Sá on 20/09/2023.
//

#pragma once
#include "Drawable.hpp"
#include "PhysicsBody.hpp"

class Projectile : public PhysicsBody, public Drawable {
public:
    Projectile(sf::Vector2f size, sf::Vector2f position, sf::Vector2f velocity);
};
