//
//  Hull.hpp
//  PleaseTanks
//
//  Created by Diniz Sá on 14/09/2023.
//

#pragma once
#include "Body.hpp"

class Gun : public Body {
private:
    float angularSpeed;
public:
    Gun(sf::Vector2f size, int spriteIndex);
    
    float getAngularSpeed();
};
