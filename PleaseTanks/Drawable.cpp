//
//  Hull.cpp
//  PleaseTanks
//
//  Created by Diniz Sá on 14/09/2023.
//

#include <cmath>

#include "AssetManager.hpp"

#include "Drawable.hpp"

Drawable::Drawable(sf::Vector2f size, Subject<sf::Vector2f>& position, Subject<float>& rotation, SpriteNames spriteName, int spriteIndex): position(position), rotation(rotation), originSpriteIndex(spriteIndex) {
    rect.setSize({size.x, size.y});
    
    const Sprite* sp = AssetManager::get()->getSprite(spriteName);
    texture = sp->getTexture();
    rect.setTexture(texture);
    setTextureSize(sp->singleImageSize);
    setSprite(spriteIndex);
    
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
void Drawable::setTextureSize(const sf::Vector2f& size) {
    textureRect.width = size.x;
    textureRect.height = size.y;
    rect.setTextureRect(textureRect);
}
void Drawable::setSprite(int index) {
    textureRect.left = textureRect.width * index;
    rect.setTextureRect(textureRect);
}
