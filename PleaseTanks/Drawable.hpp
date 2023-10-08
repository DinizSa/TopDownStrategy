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
#include "AssetManager.hpp"

class Drawable {
    using clock = std::chrono::steady_clock;
    
public:
    Drawable(sf::Vector2f size, float zIndex, SpriteNames spriteName, int spriteIndex);
    virtual ~Drawable();
    void setOpacity(sf::Uint8 opacity);
    sf::Uint8 getOpacity();
    void draw(sf::RenderWindow& window);
    void setPosition(Subject<sf::Vector2f>* position, Subject<float>* rotation);
    void setPosition(sf::Vector2f position, float rotation, bool centerWithSize = false);

    void setZIndex(int index);
    float getZIndex();
    void setColor(sf::Color color);
    
protected:
    void setSprite(int index);
    virtual void updateDrawable(){};
    void updateTexture(SpriteNames spriteName, int spriteIndex);
    bool isDirty();
    
private:
    void setSingleSpriteSize(const sf::Vector2f& size);
    
public:
    bool visible;
protected:
    bool dirty;
    sf::RectangleShape rect;
    const sf::Texture* texture;
    sf::Rect<int> textureRect;
    int zIndex;
    int currentSpriteIndex;
    const SpriteSheet* spriteSheet;
private:
    Subject<sf::Vector2f>* positionSub;
    Subject<float>* rotationSub;
    int positionOberverId, rotationOberverId;
    
private:
    static std::multimap<float, Drawable*> drawables;
public:
    static void addDrawable(Drawable* shape, float zIndex);
    static void removeDrawable(Drawable* shape);
    static void drawAll(sf::RenderWindow& window);
    static void updateDrawables();
};
