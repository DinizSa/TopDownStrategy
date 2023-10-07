#include <SFML/Graphics.hpp>
#include <functional>
#include "AssetManager.hpp"

#pragma once

class Button {
public:
    Button(sf::Vector2f position, sf::Vector2f size, std::string text, std::function<void()> onClick)
        : position(position), size(size), textString(text), onClick(onClick) {

        font = AssetManager::get()->getFont();

        // Create the button shape
        buttonShape.setSize(size);
        buttonShape.setPosition(position);
        buttonShape.setFillColor(sf::Color::Blue);

        // Create the button text
        buttonText.setFont(font);
        buttonText.setString(textString);
        buttonText.setCharacterSize(24);
        buttonText.setFillColor(sf::Color(114,73,30));

        // Center the text inside the button
        sf::FloatRect textRect = buttonText.getLocalBounds();
        buttonText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
        buttonText.setPosition(position.x + size.x / 2.0f, position.y + size.y / 2.0f);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(buttonShape);
        window.draw(buttonText);
    }

    void handleClick(sf::Vector2f mousePos) {
        if (buttonShape.getGlobalBounds().contains(mousePos)) {
            onClick();
        }
    }

private:
    sf::RectangleShape buttonShape;
    sf::Text buttonText;
    sf::Vector2f position;
    sf::Vector2f size;
    std::string textString;
    std::function<void()> onClick;
    sf::Font font;
};
