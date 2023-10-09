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
    Health(params.hp, params.armour),
    Drawable(params.sizeImage, 3.f, SpriteNames::guns, params.spriteIndex),
    gunParams(std::move(params)), dragging(false), arrowAim({60.f, 60.f}, 6, SpriteNames::arrow, 0)
{
    setPosition(&centerWorld, &rotation);
    setLocalRotationCenter(gunParams.centerPhysics);
    setLocalRotationCenter(gunParams.centerPhysics);
    setAngularSpeed(gunParams.angularSpeed);
    
    arrowAim.setVisible(false);
    arrowAim.setOrigin({0.f, 30.f});
    arrowAim.setPosition(centerWorld(), rotation());
    
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
        if (dragging)
            return;
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
bool Gun::attackPrimary(float forcePercentage) {
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
        new Projectile(pos, currentRotation, collisionMaskId, gunParams.primaryWeapon, forcePercentage);
    }
    return true;
}
std::shared_ptr<Weapon> Gun::getPrimary() const {
    return gunParams.primaryWeapon;
}
std::shared_ptr<Weapon> Gun::getSecondary() const{
    return gunParams.secondaryWeapon;
}
bool Gun::attackSecondary(float forcePercentage) {
    if (gunParams.secondaryWeapon == nullptr)
        return false;
    bool fired = gunParams.secondaryWeapon->fire();
    if (!fired)
        return false;

    float currentRotation = PhysicsBody::rotation();
    sf::Vector2f deltaPos = Utils::getVector(currentRotation, gunParams.projectileStartDistance);
    sf::Vector2f pos = centerWorld() + deltaPos;

    new Projectile(pos, currentRotation, collisionMaskId, gunParams.secondaryWeapon, forcePercentage);
    return true;
}

void Gun::update() {
    PhysicsBody::update();

    if (gunParams.primaryWeapon != nullptr)
        gunParams.primaryWeapon->updateReloadTimer();
    if (gunParams.secondaryWeapon != nullptr)
        gunParams.secondaryWeapon->updateReloadTimer();
}

void Gun::handleDrag(sf::Vector2f deltaDrag, bool isFinished) {
    float currentAngle = rect.getRotation() + 90.f;
    if (currentAngle >= 360.f)
        currentAngle = currentAngle - 360.f;
    
    float dragAngle = Utils::getAngle(deltaDrag);
    float deltaAngle = dragAngle - currentAngle;
    rotate(deltaAngle);
    
    float maxDrag = 200.f;
    float dragDistance = std::min(maxDrag,Utils::getLength(deltaDrag));
    float minScale = 1.f;
    float maxScale = 2.f;
    float arrowLength = minScale + maxScale * (dragDistance / maxDrag);
    
    
    arrowAim.setScale({arrowLength, 1.f});
    arrowAim.setVisible(true);
    
    float currentRotation = PhysicsBody::rotation();
    sf::Vector2f deltaPos = Utils::getVector(currentRotation, gunParams.projectileStartDistance);
    sf::Vector2f pos = centerWorld() + deltaPos;
    
    arrowAim.setPosition(pos, currentRotation - 90);
    
        
        
    if (!isFinished) {
        if (!dragging) {
            dragging = true;
        }
        return;
    }
    
    dragging = false;
    arrowAim.setVisible(false);
//    rect.setFillColor(sf::Color(255, 255, 255, 255));
    
    float velocityScalar = Utils::getLength(deltaDrag);
    attackPrimary(velocityScalar);
}
