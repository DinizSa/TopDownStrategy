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
void Drawable::updateDrawables() {
    for (auto drawable : Drawable::drawables) {
        drawable.second->updateDrawable();
    }
    std::erase_if(Drawable::drawables, [](const auto& pair) {
        auto const& [zIndex, drawable] = pair;
        return drawable->isDirty();
    });
}
void Drawable::drawAll(sf::RenderWindow& window) {
    for (auto drawable : Drawable::drawables) {
        drawable.second->draw(window);
    }
}

Drawable::Drawable(sf::Vector2f size, Subject<sf::Vector2f>& position, Subject<float>& rotation, float zIndex, SpriteNames spriteName, int spriteIndex): position(position), rotation(rotation), currentSpriteIndex(spriteIndex), minSpriteIndex(spriteIndex), maxSpriteIndex(spriteIndex), durationSpriteMs(0), spriteAnimationStart(std::chrono::milliseconds(0)), spriteLoop(false), dirty(false), zIndex(zIndex)
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
    
    Drawable::addDrawable(this, zIndex);
}

Drawable::~Drawable() {
    rotation.unsubscribe(this);
    position.unsubscribe(this);
    
    Drawable::removeDrawable(this);
}
bool Drawable::isDirty() {
    return dirty;
}
void Drawable::setZIndex(int index) {
    zIndex = index;
}
float Drawable::getZIndex() {
    return zIndex;
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
//            Drawable::removeDrawable(this);
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
    if (durationSpriteMs == 0)
        return;
    
    auto delta = clock::now() - spriteAnimationStart;
    auto deltaMs = delta.count() / pow(10, 6);
    
    if (deltaMs > durationSpriteMs) {
        setNextSprite();
        spriteAnimationStart = clock::now();
    }
}

void Drawable::updateDrawable() {
    updateSpriteAnimation();
};

void Drawable::draw(sf::RenderWindow& window) {
    window.draw(rect);
}
