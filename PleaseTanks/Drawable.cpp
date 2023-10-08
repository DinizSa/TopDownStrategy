//
//  Hull.cpp
//  PleaseTanks
//
//  Created by Diniz Sá on 14/09/2023.
//

#include <cmath>

#include "AssetManager.hpp"

#include "Drawable.hpp"

Drawable::Drawable(sf::Vector2f size, float zIndex, SpriteNames spriteName, int spriteIndex): currentSpriteIndex(spriteIndex), zIndex(zIndex), rotationSub(nullptr), positionSub(nullptr), dirty(false), visible(true)
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

    
    rect.setScale(spriteSheet->scale, spriteSheet->scale);
    rect.setTextureRect(textureRect);
}
void Drawable::setPosition(Subject<sf::Vector2f>* pos, Subject<float>* rot) {
    setPosition((*pos)(), (*rot)());
    
    positionSub = pos;
    std::function<void(sf::Vector2f)> callbackPosition = [&](const sf::Vector2f& newPosition) {
        rect.setPosition(newPosition.x, newPosition.y);
    };
    positionOberverId = positionSub->subscribe(callbackPosition);
    
    rotationSub = rot;
    std::function<void(float)> callbackRotation = [&](float newRotation) {
        rect.setRotation(newRotation);
    };
    rotationOberverId = rotationSub->subscribe(callbackRotation);
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
        rotationSub->unsubscribe(positionOberverId);
    
    if (positionSub != nullptr)
        positionSub->unsubscribe(rotationOberverId);
    
    Drawable::removeDrawable(this);
}
void Drawable::setZIndex(int newZIndex) {
    Drawable::removeDrawable(this);
    zIndex = newZIndex;
    Drawable::addDrawable(this, newZIndex);
}
float Drawable::getZIndex() {
    return zIndex;
}
void Drawable::setColor(sf::Color color) {
    rect.setFillColor(color);
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
    setColor(color);
}
sf::Uint8 Drawable::getOpacity() {
    auto color = rect.getFillColor();
    return color.a;
}
bool Drawable::isDirty() {
    return dirty;
}
void Drawable::draw(sf::RenderWindow& window) {
    window.draw(rect);
}
void Drawable::setVisible(bool isVisible) {
    visible = isVisible;
}
bool Drawable::isVisible() {
    return visible;
}

typedef std::multimap<float, Drawable*> Multimap;
Multimap Drawable::drawables;

void Drawable::addDrawable(Drawable* drawable, float zIndex) {
    Drawable::drawables.insert(std::pair{zIndex, drawable});
}
void Drawable::removeDrawable(Drawable* drawable) {
    for (Multimap::iterator it = Drawable::drawables.begin(); it != Drawable::drawables.end();) {
        Multimap::iterator erase_it = it++;
        if (erase_it->second == drawable && erase_it->first == drawable->zIndex) {
            Drawable::drawables.erase(erase_it);
            break;
        }
    }
}
void Drawable::drawAll(sf::RenderWindow& window) {
    for (auto drawable : Drawable::drawables) {
        if (drawable.second->visible)
            drawable.second->draw(window);
    }
}
void Drawable::updateDrawables() {
//    std::cout << Drawable::drawables.size() << std::endl;
    for (Multimap::iterator it = Drawable::drawables.begin(); it != Drawable::drawables.end();) {
        Multimap::iterator current_it = it++;
        if (current_it->second->isDirty()) {
            delete current_it->second;
        } else {
            current_it->second->updateDrawable();
        }
    }
}
