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

Tank::Tank(sf::Vector2f size, sf::Vector2f position): speed(2.f), angularSpeed(1.f), size(size), hull(size, 7), gun(size, 4), trackA({size.x/4, size.y*1.03f}, 6), trackB({size.x/4, size.y*1.03f}, 6) {
    
    int id = PhysicsBody::getAndIncrementMaskId();
    trackA.setCollisionMaskId(id);
    trackB.setCollisionMaskId(id);
    hull.setCollisionMaskId(id);
    gun.setCollisionMaskId(id);
    
    bool isTravel = false;
    sf::Vector2f deltaGun = sf::Vector2f({0.f, size.y * (0.f/10.f)});
    sf::Vector2f deltaTracks = {(2.2f/10.f) * size.x, 0};
    hull.translate(position, isTravel);
    gun.translate(position + deltaGun, isTravel);
    trackA.translate(position - deltaTracks, isTravel);
    trackB.translate(position + deltaTracks, isTravel);
}

void Tank::moveFront() {
    translate(-speed);
}
void Tank::moveBack() {
    translate(speed);
}

void Tank::rotateClock() {
    rotate(angularSpeed);
}
void Tank::rotateAntiClock() {
    rotate(-angularSpeed);
}

void Tank::rotateGunClock() {
    gun.rotateClock();
}
void Tank::rotateGunAntiClock() {
    gun.rotateAntiClock();
}

void Tank::rotate(float deltaAngle) {
    sf::Vector2f rotationOrigin = hull.getCenter();
    if (hull.rotate(deltaAngle)) {
        trackA.rotateAroundOrigin(deltaAngle, rotationOrigin);
        trackB.rotateAroundOrigin(deltaAngle, rotationOrigin);
        gun.rotateAroundOrigin(deltaAngle, rotationOrigin);
    }
}
void Tank::translate(sf::Vector2f delta) {
    if (hull.translate(delta)) {
        position += delta;
        trackA.translate(delta);
        trackB.translate(delta);
        gun.translate(delta);
    }
}
void Tank::translate(float distance) {
    float rotation = hull.getRotation();
    float rotationDeg = rotation * M_PI / 180;
    float dx = -distance * sin(rotationDeg);
    float dy = distance * cos(rotationDeg);
    
    sf::Vector2f delta = {dx, dy};
    
    if (hull.translate(delta)) {
        trackA.translate(delta);
        trackB.translate(delta);
        gun.translate(delta);
        position += delta;
    }
}
void Tank::update() {
    const sf::Vector2f& hullVelocity = hull.getVelocity();
    if (Utils::getLength(hullVelocity) > 0.01f) {
        sf::Vector2f rotationOrigin = hull.getCenter();
        if (hull.applyVelocity()) {
            gun.setVelocityAndRotateAroundOrigin(hullVelocity, rotationOrigin);
            trackA.setVelocityAndRotateAroundOrigin(hullVelocity, rotationOrigin);
            trackB.setVelocityAndRotateAroundOrigin(hullVelocity, rotationOrigin);

            gun.applyVelocity();
            trackA.applyVelocity();
            trackB.applyVelocity();
        }
    }
    
    hull.update();
    gun.update();
    trackA.update();
    trackB.update();
}

void Tank::setVelocity(sf::Vector2f velocity) {
    hull.setVelocity(velocity);
    gun.setVelocity(velocity);
    trackA.setVelocity(velocity);
    trackB.setVelocity(velocity);
    
    float imagesInitialAngle = 90.f;
    float velocityAngle = Utils::getAngle(velocity);
    float angle = imagesInitialAngle + velocityAngle;
    rotate(angle);
}
void Tank::shot() {
    bool gunAlignedWithHull = fabs(hull.getRotation() - gun.getRotation()) < 90;
    gunAlignedWithHull ? moveBack() : moveFront();
    gun.shot();
}

void Tank::travelToDestination(sf::Vector2f& destination) {
    hull.travelToDestination(destination);
}


bool Tank::contains(sf::Vector2f point) const {
    bool hitHull = hull.instersects(point);
    if (hitHull)
        std::cout << "X hull" << std::endl;
    bool hitGun = gun.instersects(point);
    if (hitGun)
        std::cout << "X gun" << std::endl;
    bool hitTrackA = trackA.instersects(point);
    if (hitTrackA)
        std::cout << "X track A" << std::endl;
    bool hitTrackB = trackB.instersects(point);
    if (hitTrackB)
        std::cout << "X track B" << std::endl;
    
    return true;
}
