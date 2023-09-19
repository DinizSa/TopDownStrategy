//
//  AssetManager.hpp
//  PleaseTanks
//
//  Created by Diniz Sá on 19/09/2023.
//

#pragma once

#include <SFML/Graphics.hpp>

class Sprite {
private:
    sf::Texture* texture;
public:
    const int columns;
    const int rows;
    const sf::Vector2f singleImageSize;
    
public:
    Sprite(int columns, int rows, std::string path, sf::Vector2f singleImageSize);
    const sf::Texture* getTexture() const;
    virtual ~Sprite();
};
