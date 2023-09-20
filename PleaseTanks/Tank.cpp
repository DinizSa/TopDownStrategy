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

Tank::Tank(sf::Vector2f size, sf::Vector2f position): speed(5.f), angularSpeed(5.f), size(size), hull(size, 7), gun(size, 4), trackA({size.x/4, size.y*1.03f}, 6), trackB({size.x/4, size.y*1.03f}, 6) {
    
    trackA.translate({(-2.2f/10.f) * size.x, 2.5f});
    trackB.translate({(2.2f/10.f) * size.x, 2.5f});
    
    int id = PhysicsBody::getAndIncrementMaskId();
    trackA.setCollisionMaskId(id);
    trackB.setCollisionMaskId(id);
    hull.setCollisionMaskId(id);
    gun.setCollisionMaskId(id);
    
    translate(position);
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
    float gunAngularSpeed = gun.getAngularSpeed();
    gun.rotate(gunAngularSpeed);
}
void Tank::rotateGunAntiClock() {
    float gunAngularSpeed = gun.getAngularSpeed();
    gun.rotate(-gunAngularSpeed);
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

void Tank::draw(sf::RenderWindow& window) {
    trackA.draw(window);
    trackB.draw(window);
    hull.draw(window);
    gun.draw(window);
}
