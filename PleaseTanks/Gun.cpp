//
//  Hull.cpp
//  PleaseTanks
//
//  Created by Diniz Sá on 14/09/2023.
//

#include "Gun.hpp"

Gun::Gun(sf::Vector2<float> size) : Drawable(size, {0.f, size.y*(-1.f/10.f)}, "/Users/Shared/merda/PleaseTanks/images/Gun_01.png") {
    setRotationCenter({size.x/2, size.y*(6.5f/10.f)});
}
