//
//  Hull.cpp
//  PleaseTanks
//
//  Created by Diniz Sá on 14/09/2023.
//

#include "Hull.hpp"

Hull::Hull(sf::Vector2<float> size) : Drawable(size, {0.f, 0.f}, "/Users/Shared/merda/PleaseTanks/images/Hull_03.png") {
}

void Hull::draw(sf::RenderWindow& window) {
    Drawable::draw(window);
}
