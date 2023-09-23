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
    
private:
    static std::multimap<float, Drawable*> drawables;
public:
    static void addDrawable(Drawable* shape, float zIndex);
    static void removeDrawable(Drawable* shape);
    static void drawAll(sf::RenderWindow& window);
    
    Subject<sf::Vector2f>& position;
    Subject<float>& rotation;

protected:
    sf::RectangleShape rect;
    const sf::Texture* texture;
    sf::Rect<int> textureRect;
    int zIndex;
    int currentSpriteIndex;
    const SpriteSheet* spriteSheet;

private:
    void setSingleSpriteSize(const sf::Vector2f& size);

protected:
    void setSprite(int index);

public:
    virtual ~Drawable();
    Drawable(sf::Vector2f size, Subject<sf::Vector2f>& position, Subject<float>& rotation, float zIndex, SpriteNames spriteName, int spriteIndex);
    void draw(sf::RenderWindow& window);

    void setZIndex(int index);
    
    float getZIndex();
};
