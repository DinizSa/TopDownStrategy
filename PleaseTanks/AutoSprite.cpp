//
//  Hull.cpp
//  PleaseTanks
//
//  Created by Diniz Sá on 14/09/2023.
//

#include <cmath>

#include "AssetManager.hpp"

#include "AutoSprite.hpp"

AutoSprite::AutoSprite(sf::Vector2f size, float zIndex, Sprite sprite): Drawable(size, zIndex, sprite.spriteName, sprite.minIndex), sprite(sprite), spriteAnimationStart(std::chrono::milliseconds(0))
{
    spriteAnimationStart = clock::now();
}
AutoSprite::~AutoSprite() {}

void AutoSprite::updateSprite(Sprite newSprite) {
    updateTexture(newSprite.spriteName, newSprite.minIndex);
    sprite = newSprite;
    spriteAnimationStart = clock::now();
    currentSpriteIndex = newSprite.minIndex;
}
void AutoSprite::setNextSprite() {
    if (currentSpriteIndex == sprite.maxIndex) {
        if (sprite.loop) {
            currentSpriteIndex = sprite.minIndex;
        } else if (sprite.singleImageDurationMs > 0) {
            sprite.endCallback();
            setNextAnimation();
            if (sprite.cleanupOnFinish) {
                dirty = true;
            }
            return;
        } else {
            currentSpriteIndex = sprite.minIndex;
        }
    } else {
        currentSpriteIndex++;
    }
    setSprite(currentSpriteIndex);
}

void AutoSprite::updateSpriteAnimation() {
    if (sprite.singleImageDurationMs == 0)
        return;

    auto delta = clock::now() - spriteAnimationStart;
    auto deltaMs = delta.count() / pow(10, 6);
    
    if (deltaMs > sprite.singleImageDurationMs) {
        setNextSprite();
        spriteAnimationStart = clock::now();
    }
}
void AutoSprite::addAnimation(Sprite sprite) {
    spritesQueue.emplace_back(sprite);
}
void AutoSprite::setAnimation(Sprite sp) {
    spritesQueue.clear();
    addAnimation(sp);
    updateSprite(sp);
}

void AutoSprite::updateDrawable() {
    updateSpriteAnimation();
}

void AutoSprite::setNextAnimation() {
    if (spritesQueue.size() > 0) {
        spritesQueue.pop_front();
    }
    if (spritesQueue.size() > 0) {
        updateSprite(spritesQueue.front());
    }
}

void AutoSprite::pauseAnimation() {
    sprite.singleImageDurationMs = 0;
    sprite.loop = false;
}
