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
void Drawable::updateDrawables() {
    for (auto drawable : Drawable::drawables) {
        drawable.second->updateDrawable();
    }
}

Drawable::Drawable(sf::Vector2f size, float zIndex, SpriteNames spriteName, int spriteIndex): currentSpriteIndex(spriteIndex), zIndex(zIndex), rotationSub(nullptr), positionSub(nullptr)
{
    rect.setSize(size);
    rect.setOrigin(size / 2.f);
    updateTexture(spriteName, spriteIndex);

    Drawable::addDrawable(this, zIndex);
}
void Drawable::updateTexture(SpriteNames spriteName, int spriteIndex) {

    spriteSheet = AssetManager::get()->getSprite(spriteName);
    texture = spriteSheet->getTexture();
    rect.setTexture(texture);
    textureRect.width = spriteSheet->singleImageSize.x;
    textureRect.height = spriteSheet->singleImageSize.y;
    
    sf::Vector2f spritePosition = spriteSheet->getPosition(spriteIndex);
    textureRect.left = spritePosition.x;
    textureRect.top = spritePosition.y;

    rect.setTextureRect(textureRect);
}
void Drawable::setPosition(Subject<sf::Vector2f>* pos, Subject<float>* rot) {
    positionSub = pos;
    std::function<void(sf::Vector2f)> callbackPosition = [&](sf::Vector2f newPosition) {
        rect.setPosition(newPosition.x, newPosition.y);
    };
    positionSub->subscribe(this, callbackPosition);
    
    rotationSub = rot;
    std::function<void(float)> callbackRotation = [&](float newRotation) {
        rect.setRotation(newRotation);
    };
    rotationSub->subscribe(this, callbackRotation);
}
void Drawable::setPosition(sf::Vector2f pos, float rot, bool centerWithSize){
    if (centerWithSize) {
        pos -= (rect.getSize()/2.f);
    }
    rect.setPosition(pos.x, pos.y);
    rect.setRotation(rot);
}

Drawable::~Drawable() {
    if (rotationSub != nullptr)
        rotationSub->unsubscribe(this);
    
    if (positionSub != nullptr)
        positionSub->unsubscribe(this);
    
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
void Drawable::setOpacity(sf::Uint8 opacity) {
    auto color = sf::Color(255, 255, 255, opacity);
    rect.setFillColor(color);
}
sf::Uint8 Drawable::getOpacity() {
    auto color = rect.getFillColor();
    return color.a;
}

void Drawable::draw(sf::RenderWindow& window) {
    window.draw(rect);
}
