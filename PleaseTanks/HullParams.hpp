//
//  Hull.hpp
//  PleaseTanks
//
//  Created by Diniz Sá on 14/09/2023.
//

#pragma once
#include <SFML/Graphics.hpp>
#include "Sound.hpp"


struct HullParams {
    sf::Vector2f imageSize, physicsSize;
    int spriteIndex;
    float maxHealth, armour, speed;
    
    std::unique_ptr<Sound> workingSound;
    std::unique_ptr<Sound> sufferDamageSound;
};

class LightHullParams: public HullParams {
public:
    LightHullParams() {
        imageSize = {100.f, 100.f};
        physicsSize = {40.f, 100.f};
        spriteIndex = 3;
        maxHealth = 200;
        armour = 30;
        speed = 2.f;
        
        workingSound = std::make_unique<Sound>(SoundNames::movingTank, 40, true);
    }
};

class MediumHullParams: public HullParams {
public:
    MediumHullParams() {
        imageSize = {100.f, 100.f};
        physicsSize = {50.f, 100.f};
        spriteIndex = 7;
        maxHealth = 300;
        armour = 50;
        speed = 1.5f;
        
        workingSound = std::make_unique<Sound>(SoundNames::movingTank, 60, true);
    }
};

class HeavyHullParams: public HullParams {
public:
    HeavyHullParams() {
        imageSize = {100.f, 100.f};
        physicsSize = {60.f, 100.f};
        spriteIndex = 5;
        maxHealth = 400;
        armour = 70;
        speed = 1.f;
        
        workingSound = std::make_unique<Sound>(SoundNames::movingTank, 60, true);
    }
};
