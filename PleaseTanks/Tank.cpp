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

Tank::Tank(sf::Vector2f size, sf::Vector2f position, HullParams hullParams, GunParams gunParams, int trackId, float angularSpeed, std::string category, Team team): CombatUnit({size.x * (6.f/10.f), size.y}, 0, 0, hullParams.speed * CONFIGS::maxDistanceBySpeedFactor, category, team, 400.f), hull(std::move(hullParams)), gun(std::move(gunParams)), trackA({size.x/4, size.y*1.03f}, trackId, 200, 50), trackB({size.x/4, size.y*1.03f}, trackId, 200, 50) {
    
    int maskId = PhysicsBody::getAndIncrementMaskId();
    setCollisionMaskId(maskId);
    trackA.setCollisionMaskId(maskId);
    trackB.setCollisionMaskId(maskId);
    hull.setCollisionMaskId(maskId);
    gun.setCollisionMaskId(maskId);
    
    setSpeed(hull.getSpeed());
    setAngularSpeed(angularSpeed);
    
    setMovementCollisions(true);
    
    bool isTravel = false;
    sf::Vector2f deltaGun = sf::Vector2f({0.f, size.y * (0.f/10.f)});
    sf::Vector2f deltaTracks = {(2.2f/10.f) * size.x, 0};
    
    PhysicsBody::translate(position, isTravel);
    hull.translate(position, isTravel);
    gun.translate(position + deltaGun, isTravel);
    trackA.translate(position - deltaTracks, isTravel);
    trackB.translate(position + deltaTracks, isTravel);
    
    maxHealth = gun.getMaxHealth() + trackA.getMaxHealth() + trackB.getMaxHealth() + hull.getMaxHealth();
    currentHealth = maxHealth;
    armour = gun.getArmour() + trackA.getArmour() + trackB.getArmour() + hull.getArmour();
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
void Tank::rotateSecondaryClock() {
    if (!canAttack())
        return;
    gun.rotateClock();
}
void Tank::rotateSecondaryAntiClock() {
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

void Tank::setVisible(bool visible) {
    hull.setVisible(visible);
    gun.setVisible(visible);
    trackA.setVisible(visible);
    trackB.setVisible(visible);
};
bool Tank::isVisible() {
    return hull.isVisible();
};

std::shared_ptr<Weapon> Tank::getPrimaryWeapon() const {
    return gun.getPrimary();
}

std::shared_ptr<Weapon> Tank::getSecondaryWeapon() const {
    return gun.getSecondary();
}

void Tank::handleDrag(sf::Vector2f deltaDrag, bool isFinished) {
    gun.handleDrag(deltaDrag, isFinished);
}
