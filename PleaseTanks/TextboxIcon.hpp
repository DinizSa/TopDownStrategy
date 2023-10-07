//
//  TextboxIcon.h
//  PleaseTanks
//
//  Created by Diniz Sá on 06/10/2023.
//

#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "AssetManager.hpp"

class TextboxIcon {
public:
    TextboxIcon(sf::Vector2f position, sf::Vector2f size, std::string content, Sprite sprite)
        : position(position), size(size) {
        
        // Create the textbox shape
        textboxShape.setSize(size);
        textboxShape.setPosition(position);
        textboxShape.setFillColor(CONFIGS::primaryColor);

        float iconPadding = 2.f;
        sf::Vector2f iconSize = {size.y - iconPadding, size.y - iconPadding};
        icon.setSize(iconSize);
        icon.setPosition(position.x + iconPadding, position.y + size.y / 2.0f - iconSize.y / 2.0f);
            

        auto spriteSheet = AssetManager::get()->getSprite(sprite.spriteName);
        sf::Vector2f spritePosition = spriteSheet->getPosition(sprite.minIndex);
        textureRect.left = spritePosition.x;
        textureRect.top = spritePosition.y;
        textureRect.width = spriteSheet->singleImageSize.x;
        textureRect.height = spriteSheet->singleImageSize.y;
        icon.setTextureRect(textureRect);
        icon.setTexture(spriteSheet->getTexture());
        
        // Create the textbox text
        text.setFont(AssetManager::get()->getFont());
        text.setString(content);
        text.setCharacterSize(16);
        text.setFillColor(sf::Color(249, 234, 154, 255));

        // Center the text vertically inside the textbox
        sf::FloatRect textRect = text.getLocalBounds();
        text.setOrigin(textRect.left + (iconSize.x + 10.f)/2.f + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
        text.setPosition(position.x + iconSize.x + 10.f + size.x / 2.0f, position.y + size.y / 2.0f);
    }
    
    void setContent(std::string& content) {
        text.setString(content);
        sf::FloatRect textRect = text.getLocalBounds();
        sf::Vector2f iconSize = icon.getSize();
        text.setOrigin(textRect.left + (iconSize.x + 10.f)/2.f + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
        text.setPosition(position.x + iconSize.x + 10.f + size.x / 2.0f, position.y + size.y / 2.0f);
    }
    
    void setTextColor(sf::Color color) {
        text.setFillColor(color);
    }
    
    void setBackgroundColor(sf::Color color) {
        textboxShape.setFillColor(color);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(textboxShape);
        window.draw(text);
        window.draw(icon);
    }

private:
    sf::RectangleShape textboxShape;
    sf::Text text;
    sf::Vector2f position;
    sf::Vector2f size;
    sf::Rect<int> textureRect;
    sf::RectangleShape icon;
};
