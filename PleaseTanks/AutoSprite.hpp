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
#include <deque>

#include "Drawable.hpp"

class AutoSprite : public Drawable {
    using clock = std::chrono::steady_clock;
    
private:
    std::deque<Sprite> spritesQueue;
protected:
    Sprite sprite;
private:
    std::chrono::time_point<clock> spriteAnimationStart;

public:
    AutoSprite(sf::Vector2f size, float zIndex, Sprite sprite);
    virtual ~AutoSprite();
private:
    void setSingleSpriteSize(const sf::Vector2f& size);
    void updateSpriteAnimation();
    void updateSprite(Sprite sprite);
    void setNextAnimation();

protected:
    void updateDrawable() override;
    void setNextSprite();

public:
    void addAnimation(Sprite sprite);
    void setAnimation(Sprite sprite);
};
