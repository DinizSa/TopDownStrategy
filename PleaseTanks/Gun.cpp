//
//  Hull.cpp
//  PleaseTanks
//
//  Created by Diniz Sá on 14/09/2023.
//

#include "Gun.hpp"
#include "Utils.hpp"
#include "Projectile.hpp"
#include "AssetManager.hpp"

Gun::Gun(sf::Vector2f imageSize, int spriteIndex) :
    PhysicsBody({imageSize.x*(3.f/10.f), imageSize.y*(6.f/10.f)}),
    Drawable(imageSize, 3.f, SpriteNames::guns, spriteIndex),
    Health(100), angularSpeed(2.f), rotationCounter(0)
{
    setPosition(&centerWorld, &rotation);
    setLocalRotationCenter({0.f, imageSize.y * (1.5f/10.f)});
}
void Gun::rotateClock() {
    rotateGun(angularSpeed);
}
void Gun::rotateAntiClock() {
    rotateGun(-angularSpeed);
}
void Gun::rotateGun(float speed) {
    if (rotationCounter == 0) {
        sf::Sound* sound = AssetManager::get()->playSound(SoundNames::rotationGunStart, audioPlayerId);
        sound->setLoop(false);
        sf::Sound* soundMoving = AssetManager::get()->playSound(SoundNames::rotationGunMoving, audioPlayerId);
        soundMoving->setLoop(true);
    }
    rotationCounter = 2;
    
    rotate(speed);
}

void Gun::shot() {
    float currentRotation = PhysicsBody::rotation();
    float radius = body.width > body.height ? body.width : body.height;
    sf::Vector2f deltaPos = Utils::getVector(currentRotation, radius);
    sf::Vector2f pos = centerWorld() + deltaPos;
    
    new FireProjectile(pos, currentRotation, collisionMaskId);
    
    Sprite sp = Sprite({SpriteNames::shotEffect, 0, 5, 80, false});
    AutoSprite* shotEffect = new AutoSprite({50.f, 50.f}, 4.f, sp);
    shotEffect->setPosition(pos, currentRotation + 90);
}

void Gun::receiveDamage(int damage) {
    updateHealth(-damage);
}

void Gun::update() {
    PhysicsBody::update();

    if (rotationCounter > 0) {
        --rotationCounter;
        if (rotationCounter == 0) {
            AssetManager::get()->stopSound(SoundNames::rotationGunMoving, audioPlayerId);
            AssetManager::get()->stopSound(SoundNames::rotationGunStart, audioPlayerId);
            auto gunStopSound = AssetManager::get()->playSound(SoundNames::rotationGunStop, audioPlayerId);
            gunStopSound->setLoop(false);
        }
    }
}
