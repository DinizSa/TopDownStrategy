//
//  Hull.cpp
//  PleaseTanks
//
//  Created by Diniz Sá on 14/09/2023.
//

#include "Gun.hpp"

Gun::Gun(sf::Vector2<float> size) : Drawable(size, "/Users/Shared/merda/PleaseTanks/images/Gun_01.png"), PhysicsBody({0.f, 0.f}, 20.f) {
}

void Gun::draw(sf::RenderWindow& window) {
    Drawable::draw(window, &combinedTransform);
    PhysicsBody::draw(window);
}
