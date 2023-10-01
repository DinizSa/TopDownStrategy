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
    Health(100)
{
    setPosition(&centerWorld, &rotation);
    setLocalRotationCenter({0.f, imageSize.y * (1.5f/10.f)});
    setAngularSpeed(2.f);
    
    primaryWeapon = std::make_unique<Weapon>(200.f, 20.f, 5.f, 4.f, 3);
    
    rotatingLocal.subscribe(this, [&](bool isRotating){
        if (isRotating) {
            sf::Sound* soundMoving = AssetManager::get()->playSound(SoundNames::rotationGun, audioPlayerId);
            soundMoving->setLoop(true);
            soundMoving->setVolume(40.f);
        } else {
            AssetManager::get()->stopSound(SoundNames::rotationGun, audioPlayerId);
            auto gunStopSound = AssetManager::get()->playSound(SoundNames::rotationGunStop, audioPlayerId);
            gunStopSound->setLoop(false);
            gunStopSound->setVolume(5.f);
        }
    });
}

bool Gun::attack() {
    bool fired = primaryWeapon->fire();
    if (!fired)
        return false;
    
    float currentRotation = PhysicsBody::rotation();
    float radius = body.width > body.height ? body.width : body.height;
    sf::Vector2f deltaPos = Utils::getVector(currentRotation, radius);
    sf::Vector2f pos = centerWorld() + deltaPos;
    
    new FireProjectile(pos, currentRotation, collisionMaskId);
    new LaunchExplosion({50.f, 50.f}, pos);
    
    return true;
}

void Gun::receiveDamage(int damage) {
    updateHealth(-damage);
}

void Gun::update() {
    PhysicsBody::update();
    primaryWeapon->updateReloadTimer();
}
