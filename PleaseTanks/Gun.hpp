//
//  Hull.hpp
//  PleaseTanks
//
//  Created by Diniz Sá on 14/09/2023.
//

#pragma once
#include "Drawable.hpp"
#include "PhysicsBody.hpp"

class Gun : public PhysicsBody, public Drawable {
private:
    float angularSpeed;
public:
    Gun(sf::Vector2f size, int spriteIndex);
    
    float getAngularSpeed();
};
