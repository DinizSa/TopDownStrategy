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

#include "Subject.hpp"
#include "Observer.hpp"
#include "AssetManager.hpp"

class Drawable : public Observer {
    using clock = std::chrono::steady_clock;
public:
    static void addDrawable(Drawable* shape, float zIndex);
    static void removeDrawable(Drawable* shape);
    static void drawAll(sf::RenderWindow& window);
    static void updateDrawables();

private:
    static std::multimap<float, Drawable*> drawables;
    
    Subject<sf::Vector2f>& position;
    Subject<float>& rotation;
    
    int minSpriteIndex;
    int maxSpriteIndex;
    int currentSpriteIndex;
    int durationSpriteMs;
    bool spriteLoop;
    const Sprite* sprite;
    std::chrono::time_point<clock> spriteAnimationStart;
    
    bool dirty;

protected:
    sf::RectangleShape rect;
    const sf::Texture* texture;
    sf::Rect<int> textureRect;
    int zIndex;

private:
    void setTextureSize(const sf::Vector2f& size);
    void setSprite(int index);
    void updateSpriteAnimation();

protected:
    void setNextSprite();

public:
    virtual ~Drawable();
    Drawable(sf::Vector2f size, Subject<sf::Vector2f>& position, Subject<float>& rotation, float zIndex, SpriteNames spriteName, int spriteIndex);
    bool isDirty();
    virtual void updateDrawable();
    void draw(sf::RenderWindow& window);
    
    void setSpriteRange(int minSpriteIndex, int maxSpriteIndex);
    void setAutomaticSprite(int timePerSpriteMs, bool spriteLoop);
    void setZIndex(int index);
    
    float getZIndex();
};
