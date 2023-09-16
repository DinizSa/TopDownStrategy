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
    sf::Vector2<float> origin;
    sf::Transform localTransform;
    
public:
    Drawable(sf::Vector2<float> size, const std::string&& texturePath);
    float getRotation();
    void translate(float delta);
    void translate(float delta, float angle);
    void translate(sf::Vector2<float> deltaPosition);
    virtual void rotate(float deltaAngle);
    virtual void rotateWithCenter(float degrees, sf::Vector2<float> center);
    virtual void draw(sf::RenderWindow& window);
};
