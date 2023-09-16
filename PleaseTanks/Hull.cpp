//
//  Hull.cpp
//  PleaseTanks
//
//  Created by Diniz Sá on 14/09/2023.
//

#include "Hull.hpp"

Hull::Hull(sf::Vector2<float> size) : Drawable(size, "/Users/Shared/merda/PleaseTanks/images/Hull_03.png") {
}

void Hull::rotate(float deltaAngle) {
    Drawable::rotate(deltaAngle);
}

void Hull::draw(sf::RenderWindow& window) {
    Drawable::draw(window);
}
