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
    CombatUnit(100), damageSmoke(nullptr)
{
    setPosition(&centerWorld, &rotation);
    setLocalRotationCenter({0.f, imageSize.y * (1.5f/10.f)});
    setAngularSpeed(2.f);
    
    primaryWeapon = std::make_shared<Weapon>(CannonHighExplosive());
    primaryWeapon->addAmmunition(10, true);
    secondaryWeapon = std::make_shared<Weapon>(AutomaticRifle());
    secondaryWeapon->addAmmunition(20, true);
    secondaryWeapon->triggerAutomatic.subscribe(this, [&](int loadedAmmo){
        attackSecondary();
    });
    
    rotatingLocal.subscribe(this, [&](bool isRotating){
        if (isRotating) {
            AssetManager::get()->playSound({SoundNames::rotationGun, 40.f, true}, audioPlayerId);
        } else {
            AssetManager::get()->stopSound(SoundNames::rotationGun, audioPlayerId);
            AssetManager::get()->playSound({SoundNames::rotationGunStop, 5.f, false}, audioPlayerId);
        }
    });
}
Gun::~Gun(){
    secondaryWeapon->triggerAutomatic.unsubscribe(this);
    rotatingLocal.unsubscribe(this);
}
bool Gun::attackPrimary() {
    bool fired = primaryWeapon->fire();
    if (primaryWeapon == nullptr)
        return false;
    if (!fired)
        return false;

    float currentRotation = PhysicsBody::rotation();
    float radius = body.width > body.height ? body.width : body.height;
    sf::Vector2f deltaPos = Utils::getVector(currentRotation, radius * 0.9f);
    sf::Vector2f pos = centerWorld() + deltaPos;

    new Projectile(pos, currentRotation, collisionMaskId, primaryWeapon);
    return true;
}
bool Gun::attackSecondary() {
    if (secondaryWeapon == nullptr)
        return false;
    bool fired = secondaryWeapon->fire();
    if (!fired)
        return false;

    float currentRotation = PhysicsBody::rotation();
    float radius = body.width > body.height ? body.width : body.height;
    sf::Vector2f deltaPos = Utils::getVector(currentRotation, radius);
    sf::Vector2f pos = centerWorld() + deltaPos;

    new Projectile(pos, currentRotation, collisionMaskId, secondaryWeapon);
    return true;
}

void Gun::receiveDamage(int damage) {
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

void Gun::update() {
    PhysicsBody::update();

    if (primaryWeapon != nullptr)
        primaryWeapon->updateReloadTimer();
    if (secondaryWeapon != nullptr)
        secondaryWeapon->updateReloadTimer();
}
