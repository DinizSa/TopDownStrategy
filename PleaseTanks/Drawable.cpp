//
//  Hull.cpp
//  PleaseTanks
//
//  Created by Diniz Sá on 14/09/2023.
//

#include "Drawable.hpp"
#include <cmath>

Drawable::Drawable(sf::Vector2f size, Subject<sf::Vector2f>& position, Subject<float>& rotation, const std::string&& texturePath) {
    rect.setSize({size.x, size.y});
    if (!texture.loadFromFile(texturePath)) {
        std::cout << "Error loading texture. Path: " << texturePath << " \n";
    }
    rect.setTexture(&texture);
    
    rect.setOrigin(size / 2.f);

    std::function<void(sf::Vector2f)> callbackPosition = [&](sf::Vector2f newPosition) {
        sf::Vector2f leftTopPosition = newPosition;
        std::cout << "new position received: " << newPosition.x << ", " << newPosition.y << std::endl;
        rect.setPosition(leftTopPosition.x, leftTopPosition.y);
    };
    position.subscribe(this, callbackPosition);
    
    std::function<void(float)> callbackRotation = [&](float newRotation) {
        std::cout << "new rotation received: " << newRotation << std::endl;
        rect.setRotation(newRotation);
    };
    rotation.subscribe(this, callbackRotation);
}

// Todo: manage unsubscriptions
//Drawable::~Drawable() {}

void Drawable::draw(sf::RenderWindow& window) {
    window.draw(rect);
}
