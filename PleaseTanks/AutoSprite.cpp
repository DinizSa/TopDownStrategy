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
    for (auto autoSprite : AutoSprite::autoSprites) {
        autoSprite->updateSpriteAnimation();
    }
    for (auto it = AutoSprite::autoSprites.begin(); it != AutoSprite::autoSprites.end();) {
        AutoSprite* autoSprite = *it;
        if (autoSprite->isDirty()) {
            delete autoSprite;
        } else {
            it++;
        }
    }
}

AutoSprite::AutoSprite(sf::Vector2f size, Subject<sf::Vector2f>& position, Subject<float>& rotation, float zIndex, Sprite sprite): Drawable(size, position, rotation, zIndex, sprite.spriteName, sprite.minIndex), sprite(sprite), spriteAnimationStart(std::chrono::milliseconds(0)), dirty(false)
{
    AutoSprite::addAutoSprite(this);
}
AutoSprite::~AutoSprite() {
    AutoSprite::removeAutoSprite(this);
}
void AutoSprite::setNextSprite() {
    if (currentSpriteIndex == sprite.maxIndex) {
        if (sprite.loop) {
            currentSpriteIndex = sprite.minIndex;
        } else if (sprite.singleImageDurationMs > 0) {
            dirty = true;
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
void AutoSprite::setSpriteRange(int min, int max) {
    currentSpriteIndex = min;
    sprite.minIndex = min;
    sprite.maxIndex = max;
}
void AutoSprite::setAutomaticSprite(int timeMs, bool loop) {
    sprite.singleImageDurationMs = timeMs;
    sprite.loop = loop;
    
    if (sprite.singleImageDurationMs > 0) {
        spriteAnimationStart = clock::now();
    }
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
