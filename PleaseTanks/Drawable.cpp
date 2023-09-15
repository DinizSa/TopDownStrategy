//
//  Hull.cpp
//  PleaseTanks
//
//  Created by Diniz Sá on 14/09/2023.
//

#include "Drawable.hpp"

Drawable::Drawable(sf::Vector2<float> size, const std::string&& texturePath) {
    
    rect.setSize({size.x, size.y});
    if (!texture.loadFromFile(texturePath)) {
        std::cout << "Error loading texture. Path: " << texturePath << " \n";
    }
    rect.setTexture(&texture);
    rect.setOrigin({size.x/2, size.y/2});
}

void Drawable::draw(sf::RenderWindow& window, const sf::Transform* transform) {
    window.draw(rect, *transform);
}
