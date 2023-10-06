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
    TextboxIcon(sf::Vector2f position, sf::Vector2f size, std::string text, sf::Texture& iconTexture)
        : position(position), size(size), textString(text) {

        font = AssetManager::get()->getFont();
        
        // Create the textbox shape
        textboxShape.setSize(size);
        textboxShape.setPosition(position);
        textboxShape.setFillColor(sf::Color::Blue);

        float iconPadding = 5.f;
        sf::Vector2f iconSize = {size.y - iconPadding, size.y - iconPadding};
        icon.setSize(iconSize);
        icon.setPosition(position.x + iconPadding, position.y + size.y / 2.0f - iconSize.y / 2.0f);
        icon.setTexture(&iconTexture);
        
        // Create the textbox text
        textText.setFont(font);
        textText.setString(textString);
        textText.setCharacterSize(24);
        textText.setFillColor(sf::Color::White);

        // Center the text vertically inside the textbox
        sf::FloatRect textRect = textText.getLocalBounds();
        textText.setOrigin(textRect.left + (iconSize.x + 10.f)/2.f + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
        textText.setPosition(position.x + iconSize.x + 10.f + size.x / 2.0f, position.y + size.y / 2.0f);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(textboxShape);
        window.draw(textText);
        window.draw(icon);
    }

private:
    sf::RectangleShape textboxShape;
    sf::Text textText;
    sf::Vector2f position;
    sf::Vector2f size;
    std::string textString;
    sf::Font font;
    
    sf::RectangleShape icon;
};
