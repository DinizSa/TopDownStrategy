//
//  StaticEnvironment.hpp
//  PleaseTanks
//
//  Created by Diniz Sá on 27/09/2023.
//

#pragma once

#include "PhysicsBody.hpp"

class Tree : public PhysicsBody {
public:
    Tree(sf::Vector2f size, sf::Vector2f position);
    virtual ~Tree();
};
