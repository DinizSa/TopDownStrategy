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
    CombatUnit(200), speed(2.f), damageSmoke(nullptr)
{
    setPosition(&centerWorld, &rotation);
    
    exhaust = new AutoSprite({{100.f, 100.f}, 2.f, {SpriteNames::effects, 0, 2, 90, true}});
    
    centerWorld.subscribe(exhaust, [&](sf::Vector2f center) {
        float currentRotation = PhysicsBody::rotation();
        float radius = (body.height / 2.f) - 5;
        sf::Vector2f deltaPos = Utils::getVector(currentRotation, radius);
        exhaustPosition = center - deltaPos;
        exhaustPosition.notify();
    });
    
    sf::Sound* sound = AssetManager::get()->playSound({SoundNames::movingTank, 10.f, true}, audioPlayerId);

    translating.subscribe(exhaust, [&](bool isMoving) {
        sound = AssetManager::get()->getPlayingSound(SoundNames::movingTank, audioPlayerId);
        if (isMoving) {
            sound->setVolume(80.f);
        } else {
            sound->setVolume(10.f);
        }
    });
}

Hull::~Hull() {
    centerWorld.unsubscribe(exhaust);
    translating.unsubscribe(exhaust);
    delete exhaust;
}

void Hull::receiveDamage(int damage) {
    bool healthRacio = updateHealth(-damage);
    
    if (healthRacio < 0.5) {
        if (damageSmoke == nullptr) {
            damageSmoke = new AutoSprite({150.f, 150.f}, 3.f, Sprite(SpriteNames::smoke, 0, 14, 90, true));
            damageSmoke->setPosition(centerWorld(), rotation());
        }
        int smokeOpacity = round((1.f - healthRacio) * 255);
        damageSmoke->setColor(sf::Color(255, 255, 255, smokeOpacity));
    }
}

void Hull::setSpeed(float newSpeed) {
    speed = newSpeed;
}

float Hull::getSpeed() const {
    return speed;
}
