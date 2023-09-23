//
//  Hull.cpp
//  PleaseTanks
//
//  Created by Diniz Sá on 14/09/2023.
//

#include <cmath>

#include "AssetManager.hpp"

#include "Drawable.hpp"

std::multimap<float, Drawable*> Drawable::drawables;

void Drawable::addDrawable(Drawable* drawable, float zIndex) {
    Drawable::drawables.insert(std::pair{zIndex, drawable});
}
void Drawable::removeDrawable(Drawable* drawable) {
    std::erase_if(Drawable::drawables, [drawable](const auto& pair) {
        auto const& [key, value] = pair;
        return value == drawable;
    });
}
void Drawable::drawAll(sf::RenderWindow& window) {
    for (auto drawable : Drawable::drawables) {
        drawable.second->draw(window);
    }
}

Drawable::Drawable(sf::Vector2f size, Subject<sf::Vector2f>& position, Subject<float>& rotation, float zIndex, SpriteNames spriteName, int spriteIndex): position(position), rotation(rotation), currentSpriteIndex(spriteIndex), zIndex(zIndex)
{
    rect.setSize({size.x, size.y});
    
    spriteSheet = AssetManager::get()->getSprite(spriteName);
    texture = spriteSheet->getTexture();
    rect.setTexture(texture);
    setSingleSpriteSize(spriteSheet->singleImageSize);
    setSprite(currentSpriteIndex);
    
    rect.setOrigin(size / 2.f);

    std::function<void(sf::Vector2f)> callbackPosition = [&](sf::Vector2f newPosition) {
        rect.setPosition(newPosition.x, newPosition.y);
    };
    position.subscribe(this, callbackPosition);
    
    std::function<void(float)> callbackRotation = [&](float newRotation) {
        rect.setRotation(newRotation);
    };
    rotation.subscribe(this, callbackRotation);
    
    Drawable::addDrawable(this, zIndex);
}

Drawable::~Drawable() {
    rotation.unsubscribe(this);
    position.unsubscribe(this);
    
    Drawable::removeDrawable(this);
}
void Drawable::setZIndex(int index) {
    zIndex = index;
}
float Drawable::getZIndex() {
    return zIndex;
}
void Drawable::setSingleSpriteSize(const sf::Vector2f& size) {
    textureRect.width = size.x;
    textureRect.height = size.y;
    rect.setTextureRect(textureRect);
}
void Drawable::setSprite(int index) {
    sf::Vector2f spritePosition = spriteSheet->getPosition(index);
    textureRect.left = spritePosition.x;
    textureRect.top = spritePosition.y;
    rect.setTextureRect(textureRect);
}

void Drawable::draw(sf::RenderWindow& window) {
    window.draw(rect);
}
