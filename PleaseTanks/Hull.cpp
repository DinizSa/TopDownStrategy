//
//  Hull.cpp
//  PleaseTanks
//
//  Created by Diniz Sá on 14/09/2023.
//

#include "Hull.hpp"
#include "Utils.hpp"

Hull::Hull(HullParams&& params) :
    PhysicsBody(params.physicsSize),
    Drawable(params.imageSize, 2.f, SpriteNames::hulls, params.spriteIndex),
    CombatUnit(params.maxHealth, params.armour), damageSmoke(nullptr), workingSound(std::move(params.workingSound))
{
    setPosition(&centerWorld, &rotation);
    
    setSpeed(params.speed);
    
    exhaust = new AutoSprite({{20.f, 20.f}, 2.f, {SpriteNames::smoke, 0, 14, 90, true}});
    exhaust->setPosition(&exhaustPosition, &rotation);
    
    centerWorld.subscribe([&](sf::Vector2f center) {
        float currentRotation = PhysicsBody::rotation();
        float radius = (body.height / 2.f) ;
        sf::Vector2f deltaPos = Utils::getVector(currentRotation, radius);
        exhaustPosition = center - deltaPos;
        exhaustPosition.notify();
    });
    
    sf::Sound* sound = AssetManager::get()->playSound(*workingSound, audioPlayerId);

    translating.subscribe([&](bool isMoving) {
        sound = AssetManager::get()->getPlayingSound(workingSound->name, audioPlayerId);
        if (isMoving) {
            sound->setVolume(workingSound->volume);
        } else {
            sound->setVolume(workingSound->volume / 10.f);
        }
    });
}

Hull::~Hull() {
    delete exhaust;
}

void Hull::receiveDamage(float damage, float armourPenetration) {
    if (!isAlive())
        return;
    
    float healthRacio = updateHealth(damage, armourPenetration);

    if (healthRacio < 0.5) {
        if (damageSmoke == nullptr) {
            damageSmoke = new AutoSprite(rect.getSize(), 3.f, Sprite(SpriteNames::smoke, 0, 14, 90, true));
            damageSmoke->setPosition(&centerWorld, &rotation);
        }
        int smokeOpacity = round((1.f - healthRacio) * 255);
        damageSmoke->setColor(sf::Color(255, 255, 255, smokeOpacity));
        
        if (healthRacio == 0.f) {
            auto explosion = new AutoSprite(rect.getSize()*2.f, 4.f, Sprite{SpriteNames::darkExplosion, 0, 8, 80, false, 1});
            explosion->setPosition(centerWorld(), 0.f);
            AssetManager::get()->playSound(Sound{SoundNames::bigExplosion, 100.f, false}, audioPlayerId);
        }
    }
}

float Hull::getSpeed() const {
    return speed;
}
