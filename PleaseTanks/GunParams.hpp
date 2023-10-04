//
//  GunParams.hpp
//  PleaseTanks
//
//  Created by Diniz Sá on 04/10/2023.
//

#pragma once

#include <SFML/Graphics.hpp>

#import "Weapon.hpp"
#import "Utils.hpp"

class GunParams {
public:
    sf::Vector2f sizeImage, sizePhysics, centerPhysics;
    float angularSpeed, hp, projectileStartDistance;
    int spriteIndex, simultaneousShots;
    std::shared_ptr<Weapon> primaryWeapon;
    std::shared_ptr<Weapon> secondaryWeapon;
};

class CannonGunParams: public GunParams {
public:
    CannonGunParams() {
        sizeImage = {100.f, 100.f};
        sizePhysics = {sizeImage.x * (3.f/10.f), sizeImage.y * (6.f/10.f)};
        centerPhysics = {0.f, sizeImage.y * (1.5f/10.f)};
        angularSpeed = 2.f;
        hp = 150;
        spriteIndex = 0;
        projectileStartDistance = Utils::getLength(sizeImage) / 2.5f;
        simultaneousShots = 1;
        
        primaryWeapon = std::make_shared<Weapon>(CannonHighExplosive());
        primaryWeapon->range = 700.f;
        primaryWeapon->reloadTimeSeconds = 6.f;
        secondaryWeapon = std::make_shared<Weapon>(AutomaticRifle());
    }
};

class SmokeGunParams: public GunParams {
public:
    SmokeGunParams() {
        sizeImage = {100.f, 100.f};
        sizePhysics = {sizeImage.x * (3.f/10.f), sizeImage.y * (6.f/10.f)};
        centerPhysics = {0.f, sizeImage.y * (0.6f/10.f)};
        angularSpeed = 2.f;
        hp = 150;
        spriteIndex = 1;
        projectileStartDistance = Utils::getLength(sizeImage) / 2.5f;
        simultaneousShots = 1;
        
        primaryWeapon = std::make_shared<Weapon>(SmokeWeapon());
        secondaryWeapon = std::make_shared<Weapon>(AutomaticRifle());
    }
};

class DoubleGunParams: public GunParams {
public:
    DoubleGunParams() {
        sizeImage = {100.f, 100.f};
        sizePhysics = {sizeImage.x * (3.f/10.f), sizeImage.y * (6.f/10.f)};
        centerPhysics = {0.f, sizeImage.y * (0.6f/10.f)};
        angularSpeed = 2.f;
        hp = 130;
        spriteIndex = 5;
        projectileStartDistance = Utils::getLength(sizeImage) / 3.f;
        simultaneousShots = 2;
        
        primaryWeapon = std::make_shared<Weapon>(AutomaticRifle());
    }
};
