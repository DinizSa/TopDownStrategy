//
//  unitHud.hpp
//  PleaseTanks
//
//  Created by Diniz Sá on 06/10/2023.
//

#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "CombatUnit.hpp"
#include "AssetManager.hpp"
#include "Button.hpp"
#include "TextboxIcon.h"

class UnitHud {
private:
    bool show;
    sf::Font font;
    sf::Text health;
    std::unique_ptr<Button> button;
    std::unique_ptr<TextboxIcon> textboxIcon;
    sf::Texture iconTexture;
    
public:
    UnitHud() {
        font = AssetManager::get()->getFont();
        health.setFont(font);
        health.setCharacterSize(20);
        health.setPosition(575.f, 750.f);
        health.setFillColor(sf::Color(255, 0, 0));
        
        
        auto onClick = []() {
            std::cout << "Button clicked!" << std::endl;
        };

        button = std::make_unique<Button>(sf::Vector2f(300, 200), sf::Vector2f(200, 50), "Click me", onClick);
        
        
        const std::string imagesPath = "/Users/Shared/merda/PleaseTanks/images/";
        if (!iconTexture.loadFromFile(imagesPath + "hearth.png")) {
            std::cerr << "Failed to load icon texture" << std::endl;
        }
        textboxIcon = std::make_unique<TextboxIcon>(sf::Vector2f(300, 400), sf::Vector2f(300, 50), "Textbox Icon", iconTexture);
    };
    void handleClick(sf::Vector2f mousePos) {
        button->handleClick(mousePos);
    }
    void setSelectedUnit(const CombatUnit* unit) {
        if (unit == nullptr) {
            show = false;
            return;
        }
        show = true;
        std::string currentHealth = std::to_string(unit->getCurrentHealth());
        currentHealth = currentHealth.substr(0, currentHealth.find(".") + 2);
        std::string maxHealth =  std::to_string(unit->getMaxHealth());
        maxHealth = maxHealth.substr(0, maxHealth.find(".") + 2);
        health.setString("HP: " + currentHealth + " / " + maxHealth);
    }
    void draw(sf::RenderWindow& window) {
        if (!show)
            return;
        window.draw(health);
        button->draw(window);
        textboxIcon->draw(window);
    }
};
