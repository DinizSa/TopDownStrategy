//
//  Hull.hpp
//  PleaseTanks
//
//  Created by Diniz Sá on 14/09/2023.
//

#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

#include "Subject.hpp"
#include "Observer.hpp"
#include "AssetManager.hpp"

class Drawable : public Observer {
private:
    Subject<sf::Vector2f>& position;
    Subject<float>& rotation;

protected:
    sf::RectangleShape rect;
    const sf::Texture* texture;
    sf::Rect<int> textureRect;
    const int minSprite;
    const int maxSprite;
    int currentSprite;

private:
    void setTextureSize(const sf::Vector2f& size);

protected:
    void setSprite(int index);
    void setNextSprite();

public:
    virtual ~Drawable();
    Drawable(sf::Vector2f size, Subject<sf::Vector2f>& position, Subject<float>& rotation, SpriteNames spriteName, int spriteIndex);
    
    virtual void draw(sf::RenderWindow& window);
};
