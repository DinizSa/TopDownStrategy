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

class Drawable : public Observer {
protected:
    sf::RectangleShape rect;
    sf::Texture texture;
    Subject<sf::Vector2f>& position;
    Subject<float>& rotation;
    
public:
    virtual ~Drawable();
    Drawable(sf::Vector2f size, Subject<sf::Vector2f>& position, Subject<float>& rotation, const std::string&& texturePath);

    virtual void draw(sf::RenderWindow& window);
};
