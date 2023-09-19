//
//  Hull.cpp
//  PleaseTanks
//
//  Created by Diniz Sá on 14/09/2023.
//

#include "Gun.hpp"

Gun::Gun(sf::Vector2f size, int spriteIndex) : Body(size, {size.x*(3.f/10.f), size.y*(6.f/10.f)}, SpriteNames::guns, spriteIndex), angularSpeed(5.f)
{
    translate({0.f, size.y * (0.f/10.f)});
    setCenterLocal({0.f, size.y * (1.5f/10.f)});
}

float Gun::getAngularSpeed() {
    return angularSpeed;
}
