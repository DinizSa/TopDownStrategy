//
//  Projectile.hpp
//  PleaseTanks
//
//  Created by Diniz Sá on 20/09/2023.
//

#pragma once

#include "PhysicsBody.hpp"

class Mine : public PhysicsBody {
public:
    Mine(sf::Vector2f position);
    ~Mine();
    void update() override;
};

class BasicMine : public Mine {
public:
    BasicMine(sf::Vector2f position);
};
