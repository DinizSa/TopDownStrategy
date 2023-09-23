//
//  Sprite.hpp
//  PleaseTanks
//
//  Created by Diniz Sá on 19/09/2023.
//

#pragma once

#include <SFML/Graphics.hpp>
#include "Sprite.hpp"

class SpriteSheet {
private:
    sf::Texture* texture;
public:
    const int columns;
    const int rows;
    const sf::Vector2f singleImageSize;
    
public:
    SpriteSheet(int columns, int rows, std::string path, sf::Vector2f singleImageSize);
    const sf::Texture* getTexture() const;
    sf::Vector2f getPosition(int index) const;
    virtual ~SpriteSheet();
};
