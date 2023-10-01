//
//  Hull.cpp
//  PleaseTanks
//
//  Created by Diniz Sá on 14/09/2023.
//

#include "Gun.hpp"
#include "Utils.hpp"
#include "Projectile.hpp"
#include "Explosion.hpp"
#include "AssetManager.hpp"

Gun::Gun(sf::Vector2f imageSize, int spriteIndex) :
    PhysicsBody({imageSize.x*(3.f/10.f), imageSize.y*(6.f/10.f)}),
    Drawable(imageSize, 3.f, SpriteNames::guns, spriteIndex),
    Health(100), rotationCounter(0)
{
    setPosition(&centerWorld, &rotation);
    setLocalRotationCenter({0.f, imageSize.y * (1.5f/10.f)});
    setAngularSpeed(2.f);
}
bool Gun::rotate(float deltaAngle) {
    if (rotationCounter == 0) {
        sf::Sound* soundMoving = AssetManager::get()->playSound(SoundNames::rotationGun, audioPlayerId);
        soundMoving->setLoop(true);
        soundMoving->setVolume(40.f);
    }
    rotationCounter = 2;
    
    return PhysicsBody::rotate(deltaAngle);
}
bool Gun::rotate(float deltaAngle, sf::Vector2f origin) {
    return PhysicsBody::rotate(deltaAngle, origin);
}

void Gun::shot() {
    float currentRotation = PhysicsBody::rotation();
    float radius = body.width > body.height ? body.width : body.height;
    sf::Vector2f deltaPos = Utils::getVector(currentRotation, radius);
    sf::Vector2f pos = centerWorld() + deltaPos;
    
    new FireProjectile(pos, currentRotation, collisionMaskId);
    new LaunchExplosion({50.f, 50.f}, pos);
}

void Gun::receiveDamage(int damage) {
    updateHealth(-damage);
}

void Gun::update() {
    PhysicsBody::update();

    if (rotationCounter > 0) {
        --rotationCounter;
        if (rotationCounter == 0) {
            AssetManager::get()->stopSound(SoundNames::rotationGun, audioPlayerId);
            auto gunStopSound = AssetManager::get()->playSound(SoundNames::rotationGunStop, audioPlayerId);
            gunStopSound->setLoop(false);
            gunStopSound->setVolume(5.f);
        }
    }
}
