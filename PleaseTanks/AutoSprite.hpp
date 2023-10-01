//
//  Hull.hpp
//  PleaseTanks
//
//  Created by Diniz Sá on 14/09/2023.
//

#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include <map>

#include "Drawable.hpp"

class AutoSprite : public Drawable {
    using clock = std::chrono::steady_clock;
    
private:
    static std::vector<AutoSprite*> autoSprites;
public:
    static void addAutoSprite(AutoSprite* autoSprite);
    static void removeAutoSprite(AutoSprite* autoSprite);
    static void updateAutoSprites();
    
protected:
    bool dirty;
    Sprite sprite;
private:
    std::function<void()> endCallback;
    std::chrono::time_point<clock> spriteAnimationStart;

private:
    void setSingleSpriteSize(const sf::Vector2f& size);
    void updateSpriteAnimation();

protected:
    void updateDrawable() override;
    void setNextSprite();
    bool isDirty();

public:
    AutoSprite(sf::Vector2f size, float zIndex, Sprite sprite);
    void updateSprite(Sprite sprite, std::function<void()> endCallback = [](){});
    virtual ~AutoSprite();
    void setEndCallback(std::function<void()> callback);
    void setIsDirty();
};
