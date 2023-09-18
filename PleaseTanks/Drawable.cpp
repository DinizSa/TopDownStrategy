//
//  Hull.cpp
//  PleaseTanks
//
//  Created by Diniz Sá on 14/09/2023.
//

#include "Drawable.hpp"
#include <cmath>

Drawable::Drawable(sf::Vector2f size, Subject<sf::Vector2f>& position, Subject<float>& rotation, const std::string&& texturePath): position(position), rotation(rotation) {
    rect.setSize({size.x, size.y});
    if (!texture.loadFromFile(texturePath)) {
        std::cout << "Error loading texture. Path: " << texturePath << " \n";
    }
    rect.setTexture(&texture);
    
    rect.setOrigin(size / 2.f);

    std::function<void(sf::Vector2f)> callbackPosition = [&](sf::Vector2f newPosition) {
        rect.setPosition(newPosition.x, newPosition.y);
    };
    position.subscribe(this, callbackPosition);
    
    std::function<void(float)> callbackRotation = [&](float newRotation) {
        rect.setRotation(newRotation);
    };
    rotation.subscribe(this, callbackRotation);
}

Drawable::~Drawable() {
    rotation.unsubscribe(this);
    position.unsubscribe(this);
}

void Drawable::draw(sf::RenderWindow& window) {
    window.draw(rect);
}
