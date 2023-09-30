//
//  Sprite.cpp
//  PleaseTanks
//
//  Created by Diniz Sá on 19/09/2023.
//

#include <cmath>
#include "SpriteSheet.hpp"

SpriteSheet::SpriteSheet(int columns, int rows, std::string path, sf::Vector2f singleImageSize, float deltaAngle): columns(columns), rows(rows), singleImageSize(singleImageSize) {
    texture = new sf::Texture;
    texture->loadFromFile(path);
}
const sf::Texture* SpriteSheet::getTexture() const {
    return texture;
}

sf::Vector2f SpriteSheet::getPosition(int index) const {
    int row = floor(index / columns);
    int column = index % columns;
    sf::Vector2f position = sf::Vector2f({column * singleImageSize.x, row * singleImageSize.y});
    return position;
}
SpriteSheet::~SpriteSheet() {
    delete texture;
}
