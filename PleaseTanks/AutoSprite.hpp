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
    bool dirty;
public:
    static void addAutoSprite(AutoSprite* autoSprite);
    static void removeAutoSprite(AutoSprite* autoSprite);
    static void updateAutoSprites();
    
protected:
    Sprite sprite;
private:
    std::chrono::time_point<clock> spriteAnimationStart;

private:
    void setSingleSpriteSize(const sf::Vector2f& size);
    void updateSpriteAnimation();

protected:
    void setNextSprite();
    bool isDirty();
    void updateDrawable() override;

public:
    AutoSprite(sf::Vector2f size, float zIndex, Sprite sprite);
    ~AutoSprite();
};
