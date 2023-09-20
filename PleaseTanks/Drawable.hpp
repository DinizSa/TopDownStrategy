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

#include "Subject.hpp"
#include "Observer.hpp"
#include "AssetManager.hpp"

class Drawable : public Observer {
    using clock = std::chrono::steady_clock;

private:
    Subject<sf::Vector2f>& position;
    Subject<float>& rotation;
    
    int minSpriteIndex;
    int maxSpriteIndex;
    int currentSpriteIndex;
    int durationSpriteMs;
    bool spriteLoop;
    const Sprite* sprite;
    
    std::chrono::time_point<clock> spriteAnimationStart;

protected:
    sf::RectangleShape rect;
    const sf::Texture* texture;
    sf::Rect<int> textureRect;

private:
    void setTextureSize(const sf::Vector2f& size);
    void setSprite(int index);
    void updateSpriteAnimation();

protected:
    void setNextSprite();

public:
    virtual ~Drawable();
    Drawable(sf::Vector2f size, Subject<sf::Vector2f>& position, Subject<float>& rotation, SpriteNames spriteName, int spriteIndex);
    
    void setSpriteIndexRange(int minSpriteIndex, int maxSpriteIndex);
    void setDynamicSprite(int timePerSpriteMs, bool spriteLoop);
    
    virtual void draw(sf::RenderWindow& window);
};
