//
//  Soldier.cpp
//  PleaseTanks
//
//  Created by Diniz Sá on 30/09/2023.
//

#include "Soldier.hpp"
#include "Projectile.hpp"
#include "Explosion.hpp"
#include "Utils.hpp"

Soldier::Soldier(sf::Vector2f size, sf::Vector2f position): PhysicsBody(size/2.f), feet(size/1.5f, 1, Sprite(SpriteNames::soldierFeet, 8, 8, 0, false)), body(size, 2, Sprite(SpriteNames::soldierMove, 0, 19, 80, true)) {

    feet.setPosition(&centerWorld, &rotation);
    body.setPosition(&centerWorld, &rotation);
    translate(position, false);

    setSpeed(1.0);
    setAngularSpeed(3.f);
    
    int id = PhysicsBody::getAndIncrementMaskId();
    setCollisionMaskId(id);
    
    setMovementCollisions(true);
    
    moving.subscribe(this, [&](bool isMoving) {
        if (isMoving) {
            feet.setAnimation(Sprite(SpriteNames::soldierFeet, 0, 19, 80, true));
        } else {
            feet.setAnimation(Sprite(SpriteNames::soldierFeet, 8, 8, 0, false));
        }
    });
    
    primaryWeapon = std::make_unique<Weapon>(Rifle());
    secondaryWeapon = std::make_unique<Weapon>(Rifle());
}
Soldier::~Soldier() {}
void Soldier::update() {
    PhysicsBody::update();
    if (primaryWeapon != nullptr)
        primaryWeapon->updateReloadTimer();
    if (secondaryWeapon != nullptr)
        secondaryWeapon->updateReloadTimer();
}

bool Soldier::attack() {
    return fireGrenade();
}

bool Soldier::fireRifle() {
    bool canAttack = primaryWeapon->fire();
    if (!canAttack)
        return false;
    body.setAnimation(Sprite(SpriteNames::soldierShoot, 0, 2, 100, false));
    body.addAnimation(Sprite(SpriteNames::soldierReload, 0, 19, 80, false));
    body.addAnimation(Sprite(SpriteNames::soldierMove, 0, 19, 80, true));
    
    sf::Sound* sound = AssetManager::get()->playSound(SoundNames::rifleReload, audioPlayerId);
    sound->setLoop(false);
    sound->setVolume(50.f);
    
    float currentRotation = PhysicsBody::rotation();
    sf::Vector2f deltaPos = Utils::getVector(currentRotation + 23.f, maxRadius + 8.f);
    sf::Vector2f pos = centerWorld() + deltaPos;
    
    new BulletProjectile(pos, currentRotation, collisionMaskId);
    new LaunchExplosion({20.f, 20.f}, pos);
    return true;
}
bool Soldier::fireGrenade() {
    bool canAttack = secondaryWeapon->fire();
    if (!canAttack)
        return false;
    
    sf::Sound* sound = AssetManager::get()->playSound(SoundNames::grenadePinPull, audioPlayerId);
    sound->setLoop(false);
    sound->setVolume(100.f);
    
    body.setAnimation(Sprite(SpriteNames::soldierGrenade, 0, 7, 100, false, [&](){
        float currentRotation = PhysicsBody::rotation();
        sf::Vector2f deltaPos = Utils::getVector(currentRotation + 23.f, maxRadius + 8.f);
        sf::Vector2f pos = centerWorld() + deltaPos;
        new GrenadeProjectile(pos, currentRotation, collisionMaskId);
    }));
    body.addAnimation(Sprite(SpriteNames::soldierMove, 0, 19, 80, true));
    
    return true;
}
