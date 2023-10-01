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

Tank::Tank(sf::Vector2f size, sf::Vector2f position): PhysicsBody({size.x * (6.f/10.f), size.y}), angularSpeed(1.f), hull(size, 7), gun(size, 4), trackA({size.x/4, size.y*1.03f}, 6), trackB({size.x/4, size.y*1.03f}, 6) {
    
    int maskId = PhysicsBody::getAndIncrementMaskId();
    setCollisionMaskId(maskId);
    trackA.setCollisionMaskId(maskId);
    trackB.setCollisionMaskId(maskId);
    hull.setCollisionMaskId(maskId);
    gun.setCollisionMaskId(maskId);
    
    setSpeed(2.f);
    setAngularSpeed(2.f);
    
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
void Tank::attack() {
    bool gunAlignedWithHull = fabs(hull.getRotation() - gun.getRotation()) < 90;
    gunAlignedWithHull ? translateBack() : translateFront();
    
    gun.shot();
}
void Tank::rotateGunClock() {
    gun.rotateClock();
}
void Tank::rotateGunAntiClock() {
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
void Tank::update() {
    PhysicsBody::update();
    
    hull.update();
    gun.update();
    trackA.update();
    trackB.update();
}
