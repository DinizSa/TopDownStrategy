//
//  Hull.cpp
//  PleaseTanks
//
//  Created by Diniz Sá on 14/09/2023.
//

#include <cmath>

#include "AssetManager.hpp"

#include "Drawable.hpp"

Drawable::Drawable(sf::Vector2f size, Subject<sf::Vector2f>& position, Subject<float>& rotation, SpriteNames spriteName, int spriteIndex): position(position), rotation(rotation), currentSpriteIndex(spriteIndex), minSpriteIndex(spriteIndex), maxSpriteIndex(spriteIndex), durationSpriteMs(0), spriteAnimationStart(std::chrono::milliseconds(0)), spriteLoop(false), dirty(false)
{
    rect.setSize({size.x, size.y});
    
    sprite = AssetManager::get()->getSprite(spriteName);
    texture = sprite->getTexture();
    rect.setTexture(texture);
    setTextureSize(sprite->singleImageSize);
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
}

Drawable::~Drawable() {
    rotation.unsubscribe(this);
    position.unsubscribe(this);
}
bool Drawable::isDirty() {
    return dirty;
}
void Drawable::setTextureSize(const sf::Vector2f& size) {
    textureRect.width = size.x;
    textureRect.height = size.y;
    rect.setTextureRect(textureRect);
}
void Drawable::setSprite(int index) {
    sf::Vector2f spritePosition = sprite->getPosition(index);
    textureRect.left = spritePosition.x;
    textureRect.top = spritePosition.y;
    rect.setTextureRect(textureRect);
}
void Drawable::setNextSprite() {
    if (currentSpriteIndex == maxSpriteIndex) {
        if (spriteLoop) {
            currentSpriteIndex = minSpriteIndex;
        } else if (durationSpriteMs > 0) {
            dirty = true;
            return;
        } else {
            currentSpriteIndex = minSpriteIndex;
        }
    } else {
        currentSpriteIndex++;
    }
    setSprite(currentSpriteIndex);
}

void Drawable::setSpriteRange(int min, int max) {
    currentSpriteIndex = min;
    minSpriteIndex = min;
    maxSpriteIndex = max;
}
void Drawable::setAutomaticSprite(int timeMs, bool loop) {
    durationSpriteMs = timeMs;
    spriteLoop = loop;
    
    if (durationSpriteMs > 0) {
        spriteAnimationStart = clock::now();
    }
}

void Drawable::updateSpriteAnimation() {
    auto delta = clock::now() - spriteAnimationStart;
    auto deltaMs = delta.count() / pow(10, 6);
    
    if (deltaMs > durationSpriteMs) {
        setNextSprite();
        spriteAnimationStart = clock::now();
    }
}

void Drawable::draw(sf::RenderWindow& window) {
    
    if (durationSpriteMs > 0) {
        updateSpriteAnimation();
    }
    
    window.draw(rect);
}
