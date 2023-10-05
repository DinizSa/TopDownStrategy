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

Soldier::Soldier(sf::Vector2f size, sf::Vector2f position): PhysicsBody(size/2.f), feet(size/1.5f, 1.f, Sprite(SpriteNames::soldierFeet, 8, 8, 0, false)), soldierBody(size, 2.f, Sprite(SpriteNames::soldierMove, 0, 19, 80, true)), CombatUnit(100, 10) {

    feet.setPosition(&centerWorld, &rotation);
    soldierBody.setPosition(&centerWorld, &rotation);
    translate(position, false);

    setSpeed(1.0);
    setAngularSpeed(3.f);
    
    int id = PhysicsBody::getAndIncrementMaskId();
    setCollisionMaskId(id);
    
    setMovementCollisions(true);
    
    translatingOberverId = translating.subscribe([&](bool isMoving) {
        if (isMoving)
            feet.setAnimation(Sprite(SpriteNames::soldierFeet, 0, 19, 80, true));
        else if (!rotatingLocal())
            feet.setAnimation(Sprite(SpriteNames::soldierFeet, 8, 8, 0, false));
    });
    rotatingLocalOberverId = rotatingLocal.subscribe([&](bool rotating) {
        if (rotating)
            feet.setAnimation(Sprite(SpriteNames::soldierFeet, 0, 19, 80, true));
        else if (!translating())
            feet.setAnimation(Sprite(SpriteNames::soldierFeet, 8, 8, 0, false));
    });
    
    primaryWeapon = std::make_shared<Weapon>(Rifle());
    primaryWeapon->addAmmunition(8, true);
    secondaryWeapon = std::make_shared<Weapon>(Grenade());
    secondaryWeapon->addAmmunition(8, true);
}
Soldier::~Soldier() {
    rotatingLocal.unsubscribe(translatingOberverId);
    translating.unsubscribe(rotatingLocalOberverId);
}

void Soldier::update() {
    PhysicsBody::update();
    if (primaryWeapon != nullptr)
        primaryWeapon->updateReloadTimer();
    if (secondaryWeapon != nullptr)
        secondaryWeapon->updateReloadTimer();
}

bool Soldier::attackPrimary() {
    return fireRifle();
}

bool Soldier::attackSecondary() {
    return fireGrenade();
}

bool Soldier::fireRifle() {
    bool canAttack = primaryWeapon->fire();
    if (!canAttack)
        return false;
    
    float currentRotation = PhysicsBody::rotation();
    sf::Vector2f deltaPos = Utils::getVector(currentRotation + 23.f, maxRadius + 8.f);
    sf::Vector2f pos = centerWorld() + deltaPos;
    
    new Projectile(pos, currentRotation, collisionMaskId, primaryWeapon);
    
    soldierBody.setAnimation(Sprite(SpriteNames::soldierShoot, 0, 2, 100, false));
    if (primaryWeapon->isReloading()) {
        AssetManager::get()->playSound({SoundNames::rifleReload, 50.f, false}, audioPlayerId);
        soldierBody.addAnimation(Sprite(SpriteNames::soldierReload, 0, 19, 80, false));
    }
    soldierBody.addAnimation(Sprite(SpriteNames::soldierMove, 0, 19, 80, true));
    return true;
}
bool Soldier::fireGrenade() {
    bool canAttack = secondaryWeapon->fire();
    if (!canAttack)
        return false;
    
    AssetManager::get()->playSound({SoundNames::grenadePinPull, 50.f, false}, audioPlayerId);
    
    soldierBody.setAnimation(Sprite(SpriteNames::soldierGrenade, 0, 7, 80, false, 1, [&](){
        float currentRotation = PhysicsBody::rotation();
        sf::Vector2f deltaPos = Utils::getVector(currentRotation + 23.f, maxRadius + 8.f);
        sf::Vector2f pos = centerWorld() + deltaPos;
        new Projectile(pos, currentRotation, collisionMaskId, secondaryWeapon);
    }));
    soldierBody.addAnimation(Sprite(SpriteNames::soldierMove, 0, 19, 80, true));
    
    return true;
}

void Soldier::receiveDamage(float damage, float armourPenetration) {
    bool survived = updateHealth(damage, armourPenetration) > 0.f;
    
    AssetManager::get()->playSound({SoundNames::hurt, 50.f, false}, audioPlayerId);
    auto blood = new AutoSprite({50.f, 50.f}, 3.f, Sprite(SpriteNames::blood, 0, 5, 80, false, 1));
    blood->setPosition(centerWorld(), rotation());
    blood->setColor(sf::Color(255, 255, 255, 180));
    
    if (!survived) {
        soldierBody.setColor(sf::Color(255, 0, 0, 100));
        feet.setColor(sf::Color(0, 0, 0, 0));
        feet.setZIndex(0.f);
        soldierBody.setZIndex(0.f);
        PhysicsBody::removeCollider();
        soldierBody.pauseAnimation();
        return;
    }
}
