//
//  Hull.cpp
//  PleaseTanks
//
//  Created by Diniz Sá on 14/09/2023.
//

#include "Gun.hpp"

Gun::Gun(sf::Vector2f size) : Body(size, "/Users/Shared/merda/PleaseTanks/images/Gun_01.png"), angularSpeed(5.f)
{
    translate({0.f, size.y*(0.f/10.f)});
//    setRotationCenter({size.x/2, size.y*(6.5f/10.f)});
}

float Gun::getAngularSpeed() {
    return angularSpeed;
}
