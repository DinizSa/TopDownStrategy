//
//  Hull.cpp
//  PleaseTanks
//
//  Created by Diniz Sá on 14/09/2023.
//

#include "Gun.hpp"

Gun::Gun(sf::Vector2<float> size) : Drawable(size, "/Users/Shared/merda/PleaseTanks/images/Gun_01.png") {
    setRotationCenter({size.x/2, size.y*(5.5f/10.f)});
    translate(size.y/10.f);
}

void Gun::rotate(float deltaAngle) {
    Drawable::rotate(deltaAngle);
}

void Gun::draw(sf::RenderWindow& window) {
    Drawable::draw(window);
}
