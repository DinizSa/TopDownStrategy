//
//  Soldier.hpp
//  PleaseTanks
//
//  Created by Diniz Sá on 30/09/2023.
//

#include <SFML/Graphics.hpp>

#include "PhysicsBody.hpp"
#include "AutoSprite.hpp"

#pragma once

class Soldier : public PhysicsBody {
private:
    AutoSprite feet;
    AutoSprite body;
public:
    Soldier(sf::Vector2f size, sf::Vector2f position);
    ~Soldier();
    void update() override;
};
