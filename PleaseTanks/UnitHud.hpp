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
#include "TextboxIcon.hpp"
#include "Configs.hpp"

struct WeaponHud {
    std::unique_ptr<TextboxIcon> name, description, range, damage, explosionRadius, armorPenetration;
    void draw(sf::RenderWindow& window) {
        name->draw(window);
        range->draw(window);
        damage->draw(window);
        explosionRadius->draw(window);
        armorPenetration->draw(window);
    }
};

class UnitHud {
private:
    bool show;
    std::unique_ptr<TextboxIcon> name, health, armour, speed;
    std::unique_ptr<WeaponHud> primaryWeaponHud, secondaryWeaponHud;
    
    int height = 25;
    int padY = 3;
    int startY = 688;
    int startX;
    int width = 200;
public:
    UnitHud() {};
    void handleClick(sf::Vector2f mousePos) {}
    void setSelectedUnit(const CombatUnit* unit) {
        if (unit == nullptr) {
            show = false;
            return;
        }
        show = true;
        startX = 5;
        
        std::string nameString = "Tank";
        int y = startY;
        name = std::make_unique<TextboxIcon>(sf::Vector2f(startX, y), sf::Vector2f(width, height), nameString, Sprite(SpriteNames::icons, -1, 0, 0, false));
        name->setTextColor(CONFIGS::primaryColor);
        name->setBackgroundColor(CONFIGS::baseColor);
        
        y += padY + height;
        std::string healthString = Utils::floatToString(unit->getCurrentHealth(), 2) + " / " + Utils::floatToString(unit->getMaxHealth(), 2) + " HP";
        health = std::make_unique<TextboxIcon>(sf::Vector2f(startX, y), sf::Vector2f(width, height), healthString, Sprite(SpriteNames::icons, 0, 0, 0, false));
        
        y += padY + height;
        std::string armorString = Utils::floatToString(unit->getArmour(), 2) + " armour";
        armour = std::make_unique<TextboxIcon>(sf::Vector2f(startX, y), sf::Vector2f(width, height), armorString, Sprite(SpriteNames::icons, 5, 0, 0, false));
        
        y += padY + height;
        std::string speedString = Utils::floatToString(unit->getSpeed(), 2) + " speed";
        speed = std::make_unique<TextboxIcon>(sf::Vector2f(startX, y), sf::Vector2f(width, height), speedString, Sprite(SpriteNames::icons, 1, 0, 0, false));
        
        
        std::shared_ptr<Weapon> weapon = unit->getPrimaryWeapon();
        setupWeapon(weapon, primaryWeaponHud);
        
        weapon = unit->getSecondaryWeapon();
        setupWeapon(weapon, secondaryWeaponHud);
    }
    void setupWeapon(std::shared_ptr<Weapon> weapon, std::unique_ptr<WeaponHud>& weaponHud) {
        if (weapon == nullptr) {
            weaponHud = nullptr;
            return;
        }
        
        startX += width + padY;
        int y = startY;
        
        std::string damage = Utils::floatToString(weapon->damage, 2) + " damage";
        std::string rangeString = Utils::floatToString(weapon->range, 2) + " range";
        std::string explosionRadiusString = Utils::floatToString(weapon->explosionPhysicsSize.x, 2) + " radius";
        std::string armorPenetrationString = Utils::floatToString(weapon->penetration, 2) + " penetration";
        
        if (weaponHud == nullptr) {
            weaponHud = std::make_unique<WeaponHud>();
            weaponHud->name = std::make_unique<TextboxIcon>(sf::Vector2f(startX, y), sf::Vector2f(width, height), weapon->name, Sprite(SpriteNames::icons, -1, 0, 0, false));
            weaponHud->name->setTextColor(CONFIGS::primaryColor);
            weaponHud->name->setBackgroundColor(CONFIGS::baseColor);
            
            y += padY + height;
            weaponHud->damage = std::make_unique<TextboxIcon>(sf::Vector2f(startX, y), sf::Vector2f(width, height), damage, Sprite(SpriteNames::icons, 7, 0, 0, false));
            
            y += padY + height;
            weaponHud->range = std::make_unique<TextboxIcon>(sf::Vector2f(startX, y), sf::Vector2f(width, height), rangeString, Sprite(SpriteNames::icons, 2, 0, 0, false));
            
            y += padY + height;
            weaponHud->armorPenetration = std::make_unique<TextboxIcon>(sf::Vector2f(startX, y), sf::Vector2f(width, height), armorPenetrationString, Sprite(SpriteNames::icons, 6, 0, 0, false));
            
            y += padY + height;
            weaponHud->explosionRadius = std::make_unique<TextboxIcon>(sf::Vector2f(startX, y), sf::Vector2f(width, height), explosionRadiusString, Sprite(SpriteNames::icons, 8, 0, 0, false));
        } else {
            weaponHud->name->setContent(weapon->name);
            weaponHud->damage->setContent(damage);
            weaponHud->range->setContent(rangeString);
            weaponHud->armorPenetration->setContent(armorPenetrationString);
            weaponHud->explosionRadius->setContent(explosionRadiusString);
        }
    }
    
    void draw(sf::RenderWindow& window) {
        if (!show)
            return;
        name->draw(window);
        health->draw(window);
        armour->draw(window);
        speed->draw(window);
        
        if (primaryWeaponHud != nullptr)
            primaryWeaponHud->draw(window);
        if (secondaryWeaponHud != nullptr)
            secondaryWeaponHud->draw(window);
    }
};
