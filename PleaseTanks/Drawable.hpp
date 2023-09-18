//
//  Hull.hpp
//  PleaseTanks
//
//  Created by Diniz Sá on 14/09/2023.
//

#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Drawable {
protected:
    sf::RectangleShape rect;
    sf::Texture texture;
    sf::Vector2<float> deltaCenter;
    
public:
    Drawable(sf::Vector2<float> size, sf::Vector2<float> position, const std::string&& texturePath);
    virtual void setRotationCenter(sf::Vector2<float>&& center);
    virtual void setDeltaCenter(sf::Vector2<float> deltaCenter);

    virtual void translate(float delta);
    virtual void translate(sf::Vector2<float> delta);
    virtual void rotate(float deltaAngle);
    virtual void rotateAroundParent(float currentAngle, float degrees);
    
    virtual void draw(sf::RenderWindow& window);
};
