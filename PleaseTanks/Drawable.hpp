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
    Drawable(sf::Vector2<float> size, sf::Vector2<float> deltaCenter, const std::string&& texturePath);
    float getRotation();
    void setRotationCenter(sf::Vector2<float> center);
    
    void translate(float delta);
    void translate(float delta, float angle);
    void translate(sf::Vector2<float> deltaPosition);
    virtual void rotate(float deltaAngle);
    virtual void rotateAroundParent(float currentAngle, float degrees);
    virtual void draw(sf::RenderWindow& window);
};
