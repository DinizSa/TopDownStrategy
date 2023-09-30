//
//  Hull.cpp
//  PleaseTanks
//
//  Created by Diniz Sá on 14/09/2023.
//

#include "Hull.hpp"
#include "Utils.hpp"

Hull::Hull(sf::Vector2f imageSize, int spriteIndex) :
    PhysicsBody({imageSize.x * (6.f/10.f), imageSize.y}),
    Drawable(imageSize, 2.f, SpriteNames::hulls, spriteIndex),
    Health(200), movingCounter(0), speed(2.f)
{
    setPosition(&centerWorld, &rotation);
    
    exhaust = new AutoSprite({{100.f, 100.f}, 2.f, {SpriteNames::effects, 0, 2, 90, true}});
    exhaust->setPosition(&exhaustPosition, &rotation);
    
    PhysicsBody::centerWorld.subscribe(exhaust, [&](sf::Vector2f center) {
        float currentRotation = PhysicsBody::rotation();
        float radius = (body.height / 2.f) - 5;
        sf::Vector2f deltaPos = Utils::getVector(currentRotation, radius);
        exhaustPosition = center - deltaPos;
        exhaustPosition.notify();
    });
    
    PhysicsBody::traveledDistance.subscribe(exhaust, [&](float distance) {
        if (movingCounter == 0) {
            sf::Sound* sound = AssetManager::get()->getPlayingSound(SoundNames::movingTank, audioPlayerId);
            if (sound == nullptr) {
                sound = AssetManager::get()->playSound(SoundNames::movingTank, audioPlayerId);
                sound->setLoop(true);
            } else {
                sound->setVolume(100.f);
            }
        }
        movingCounter = 2;
    });
}

Hull::~Hull() {
    delete exhaust;
}

void Hull::receiveDamage(int damage) {
    updateHealth(-damage);
}

void Hull::update() {
    PhysicsBody::update();
    
    if (movingCounter > 0) {
        --movingCounter;
        if (movingCounter == 0) {
            sf::Sound* sound = AssetManager::get()->getPlayingSound(SoundNames::movingTank, audioPlayerId);
            if (sound != nullptr) {
                sound->setVolume(30.f);
            }
        }
    }
}
void Hull::setSpeed(float newSpeed) {
    speed = newSpeed;
}

float Hull::getSpeed() const {
    return speed;
}
