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

Gun::Gun(GunParams&& params) :
    PhysicsBody(params.sizePhysics),
    Drawable(params.sizeImage, 3.f, SpriteNames::guns, params.spriteIndex),
    CombatUnit(params.hp), gunParams(std::move(params))
{
    setPosition(&centerWorld, &rotation);
    setLocalRotationCenter(gunParams.centerPhysics);
    setAngularSpeed(gunParams.angularSpeed);
    
    
    if (gunParams.primaryWeapon != nullptr) {
        this->gunParams.primaryWeapon->addAmmunition(10, true);
        gunParams.primaryWeapon->addAmmunition(20, true);
        if (gunParams.primaryWeapon->automatic) {
            gunParams.primaryWeapon->triggerAutomatic.subscribe([&](int loadedAmmo){
                attackPrimary();
            });
        }
    }
    if (gunParams.secondaryWeapon != nullptr) {
        gunParams.secondaryWeapon->addAmmunition(20, true);
        if (gunParams.secondaryWeapon->automatic) {
            gunParams.secondaryWeapon->triggerAutomatic.subscribe([&](int loadedAmmo){
                attackSecondary();
            });
        }
    }
    
    rotatingLocal.subscribe([&](bool isRotating){
        if (isRotating) {
            AssetManager::get()->playSound({SoundNames::rotationGun, 40.f, true}, audioPlayerId);
        } else {
            AssetManager::get()->stopSound(SoundNames::rotationGun, audioPlayerId);
            AssetManager::get()->playSound({SoundNames::rotationGunStop, 5.f, false}, audioPlayerId);
        }
    });
}
Gun::~Gun(){
}

void Gun::setupGun(int initialAmmunition) {
    
}
bool Gun::attackPrimary() {
    bool fired = gunParams.primaryWeapon->fire();
    if (gunParams.primaryWeapon == nullptr)
        return false;
    if (!fired)
        return false;

    float currentRotation = PhysicsBody::rotation();

    float startPosDelta = (gunParams.simultaneousShots - 1)/2.f;
    for (int i = 0; i < gunParams.simultaneousShots; i++) {
        float deltaAngle = (i - startPosDelta) * 10.f;
        sf::Vector2f deltaPos = Utils::getVector(currentRotation + deltaAngle, gunParams.projectileStartDistance);
        sf::Vector2f pos = centerWorld() + deltaPos;
        new Projectile(pos, currentRotation, collisionMaskId, gunParams.primaryWeapon);
    }
    return true;
}
bool Gun::attackSecondary() {
    if (gunParams.secondaryWeapon == nullptr)
        return false;
    bool fired = gunParams.secondaryWeapon->fire();
    if (!fired)
        return false;

    float currentRotation = PhysicsBody::rotation();
    float radius = body.width > body.height ? body.width : body.height;
    sf::Vector2f deltaPos = Utils::getVector(currentRotation, gunParams.projectileStartDistance);
    sf::Vector2f pos = centerWorld() + deltaPos;

    new Projectile(pos, currentRotation, collisionMaskId, gunParams.secondaryWeapon);
    return true;
}

void Gun::receiveDamage(int damage) {
    updateHealth(-damage);
}

void Gun::update() {
    PhysicsBody::update();

    if (gunParams.primaryWeapon != nullptr)
        gunParams.primaryWeapon->updateReloadTimer();
    if (gunParams.secondaryWeapon != nullptr)
        gunParams.secondaryWeapon->updateReloadTimer();
}
