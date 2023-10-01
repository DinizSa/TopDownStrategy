//
//  Hull.cpp
//  PleaseTanks
//
//  Created by Diniz Sá on 14/09/2023.
//

#include <cmath>

#include "AssetManager.hpp"

#include "AutoSprite.hpp"

std::vector<AutoSprite*> AutoSprite::autoSprites;

void AutoSprite::addAutoSprite(AutoSprite* autoSprite) {
    AutoSprite::autoSprites.push_back(autoSprite);
}
void AutoSprite::removeAutoSprite(AutoSprite* autoSprite) {
    AutoSprite::autoSprites.erase(std::remove(AutoSprite::autoSprites.begin(), AutoSprite::autoSprites.end(), autoSprite), AutoSprite::autoSprites.end());
}
void AutoSprite::updateAutoSprites() {
    for (auto it = AutoSprite::autoSprites.begin(); it != AutoSprite::autoSprites.end();) {
        AutoSprite* autoSprite = *it;
        if (autoSprite->isDirty()) {
            delete autoSprite;
        } else {
            it++;
        }
    }
}

AutoSprite::AutoSprite(sf::Vector2f size, float zIndex, Sprite sprite): Drawable(size, zIndex, sprite.spriteName, sprite.minIndex), sprite(sprite), spriteAnimationStart(std::chrono::milliseconds(0)), dirty(false), endCallback([](){})
{
    spriteAnimationStart = clock::now();
    
    AutoSprite::addAutoSprite(this);
}
AutoSprite::~AutoSprite() {
    AutoSprite::removeAutoSprite(this);
}
void AutoSprite::updateSprite(Sprite newSprite, std::function<void()> finishCallback) {
    updateTexture(newSprite.spriteName, newSprite.minIndex);
    sprite = newSprite;
    spriteAnimationStart = clock::now();
    currentSpriteIndex = newSprite.minIndex;
    endCallback = finishCallback;
}
void AutoSprite::setNextSprite() {
    if (currentSpriteIndex == sprite.maxIndex) {
        if (sprite.loop) {
            currentSpriteIndex = sprite.minIndex;
        } else if (sprite.singleImageDurationMs > 0) {
            spriteAnimationStart = clock::now();
            sprite.singleImageDurationMs = 0;
            sprite.loop = false;
            endCallback();
            return;
        } else {
            currentSpriteIndex = sprite.minIndex;
        }
    } else {
        currentSpriteIndex++;
    }
    setSprite(currentSpriteIndex);
}

bool AutoSprite::isDirty() {
    return dirty;
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

void AutoSprite::updateDrawable() {
    updateSpriteAnimation();
}

void AutoSprite::setEndCallback(std::function<void()> callback) {
    endCallback = std::move(callback);
}
