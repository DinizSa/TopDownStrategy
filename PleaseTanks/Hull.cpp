//
//  Hull.cpp
//  PleaseTanks
//
//  Created by Diniz Sá on 14/09/2023.
//

#include "Hull.hpp"

Hull::Hull(sf::Vector2<float> size) : Drawable(size, "/Users/Shared/merda/PleaseTanks/images/Hull_03.png"), PhysicsBody({0.f, 0.f}, 20.f) {
}

void Hull::draw(sf::RenderWindow& window) {
    Drawable::draw(window, &transform);
    PhysicsBody::draw(window);
}
