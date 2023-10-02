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
    
    primaryWeapon = std::make_shared<Weapon>(Rifle());
    
    rotatingLocal.subscribe(this, [&](bool isRotating){
        if (isRotating) {
            AssetManager::get()->playSound({SoundNames::rotationGun, 40.f, true}, audioPlayerId);
        } else {
            AssetManager::get()->stopSound(SoundNames::rotationGun, audioPlayerId);
            AssetManager::get()->playSound({SoundNames::rotationGunStop, 5.f, false}, audioPlayerId);
        }
    });
}

bool Gun::attackPrimary() {
    return true;
}
bool Gun::attackSecondary() {
//    bool fired = primaryWeapon->fire();
//    if (!fired)
//        return false;
//
//    float currentRotation = PhysicsBody::rotation();
//    float radius = body.width > body.height ? body.width : body.height;
//    sf::Vector2f deltaPos = Utils::getVector(currentRotation, radius);
//    sf::Vector2f pos = centerWorld() + deltaPos;
//
//    new FireProjectile(pos, currentRotation, collisionMaskId);
//    new LaunchExplosion({50.f, 50.f}, pos);
//
    return true;
}

void Gun::receiveDamage(int damage) {
    updateHealth(-damage);
}

void Gun::update() {
    PhysicsBody::update();
    primaryWeapon->updateReloadTimer();
}
