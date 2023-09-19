//
//  Sprite.cpp
//  PleaseTanks
//
//  Created by Diniz Sá on 19/09/2023.
//

#include "Sprite.hpp"

Sprite::Sprite(int columns, int rows, std::string path, sf::Vector2f singleImageSize): columns(columns), rows(rows), singleImageSize(singleImageSize) {
    texture = new sf::Texture;
    texture->loadFromFile(path);
}
const sf::Texture* Sprite::getTexture() const {
    return texture;
}
Sprite::~Sprite() {
    delete texture;
}
