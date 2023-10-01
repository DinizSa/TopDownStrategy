//
//  Soldier.hpp
//  PleaseTanks
//
//  Created by Diniz Sá on 30/09/2023.
//

#include <SFML/Graphics.hpp>

#include "PhysicsBody.hpp"
#include "AutoSprite.hpp"
#include "Observer.hpp"
#include "CombatUnit.hpp"

#pragma once

class Soldier : public PhysicsBody, public CombatUnit, private Observer {
private:
    AutoSprite feet;
    AutoSprite body;
public:
    Soldier(sf::Vector2f size, sf::Vector2f position);
    ~Soldier();
    
    void attack() override;
};
