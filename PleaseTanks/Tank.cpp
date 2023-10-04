//
//  Tank.cpp
//  PleaseTanks
//
//  Created by Diniz Sá on 14/09/2023.
//
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

#include "Tank.hpp"
#include "Utils.hpp"
#include "GunParams.hpp"

Tank::Tank(sf::Vector2f size, sf::Vector2f position): PhysicsBody({size.x * (6.f/10.f), size.y}), angularSpeed(1.f), hull(size, 7), gun(CannonPenetrationGunParams()), trackA({size.x/4, size.y*1.03f}, 6), trackB({size.x/4, size.y*1.03f}, 6), CombatUnit(300) {
    
    int maskId = PhysicsBody::getAndIncrementMaskId();
    setCollisionMaskId(maskId);
    trackA.setCollisionMaskId(maskId);
    trackB.setCollisionMaskId(maskId);
    hull.setCollisionMaskId(maskId);
    gun.setCollisionMaskId(maskId);
    
    setSpeed(2.f);
    setAngularSpeed(1.5f);
    
    setMovementCollisions(true);
    
    bool isTravel = false;
    sf::Vector2f deltaGun = sf::Vector2f({0.f, size.y * (0.f/10.f)});
    sf::Vector2f deltaTracks = {(2.2f/10.f) * size.x, 0};
    
    PhysicsBody::translate(position, isTravel);
    hull.translate(position, isTravel);
    gun.translate(position + deltaGun, isTravel);
    trackA.translate(position - deltaTracks, isTravel);
    trackB.translate(position + deltaTracks, isTravel);
}
bool Tank::attackPrimary() {
    if (!canAttack())
        return false;
    return gun.attackPrimary();
}
bool Tank::attackSecondary() {
    if (!canAttack())
        return false;
    return gun.attackSecondary();
}
void Tank::rotateGunClock() {
    if (!canAttack())
        return;
    gun.rotateClock();
}
void Tank::rotateGunAntiClock() {
    if (!canAttack())
        return;
    gun.rotateAntiClock();
}

bool Tank::rotate(float deltaAngle) {
    sf::Vector2f rotationCenter = getCenter();
    if (!PhysicsBody::rotate(deltaAngle))
        return false;
    
    hull.rotate(deltaAngle, rotationCenter);
    trackA.rotate(deltaAngle, rotationCenter);
    trackB.rotate(deltaAngle, rotationCenter);
    gun.rotate(deltaAngle, rotationCenter);
    return true;
}
bool Tank::translate(sf::Vector2f delta, bool isTravel) {
    if (!canMove())
        return false;
    bool translated = PhysicsBody::translate(delta, isTravel);
    if (!translated)
        return false;
    
    hull.translate(delta);
    trackA.translate(delta);
    trackB.translate(delta);
    gun.translate(delta);
    return translated;
}
bool Tank::translate(float distance, bool isTravel) {
    float rotation = hull.getRotation();
    float rotationDeg = rotation * M_PI / 180;
    float dx = -distance * sin(rotationDeg);
    float dy = distance * cos(rotationDeg);
    
    sf::Vector2f delta = {dx, dy};
    
    return translate(delta);
}

bool Tank::canMove() {
    return hull.isAlive() && trackA.isAlive() && trackB.isAlive();
}
bool Tank::canAttack() {
    return gun.isAlive();
}

void Tank::receiveDamage(int damage) {
    float healthRacio = CombatUnit::updateHealth(-damage);
    if (healthRacio == 0.f) {
        auto explosion = new AutoSprite({250.f, 250.f}, 4.f, Sprite{SpriteNames::darkExplosion, 0, 8, 80, false, true});
        explosion->setPosition(centerWorld(), 0.f);
        AssetManager::get()->playSound(Sound{SoundNames::bigExplosion, 100.f, false}, audioPlayerId);
    }
}
