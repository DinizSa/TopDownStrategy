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
    
public:
    Drawable(sf::Vector2<float> size, sf::Vector2<float> position, const std::string&& texturePath);
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual void draw(sf::RenderWindow& window, const sf::Transform* transform);
};
