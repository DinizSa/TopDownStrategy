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

Tank::Tank(sf::Vector2f size, sf::Vector2f position): speed(5.f), angularSpeed(5.f), size(size), hull(size), gun(size), trackA({size.x/4, size.y}), trackB({size.x/4, size.y}) {
    
    trackA.translate({(-2.f/10.f) * size.x, 0});
    trackB.translate({(2.f/10.f) * size.x, 0});
    
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
    trackA.rotateAroundOrigin(deltaAngle, rotationOrigin);
    trackB.rotateAroundOrigin(deltaAngle, rotationOrigin);
    gun.rotateAroundOrigin(deltaAngle, rotationOrigin);
    hull.rotate(deltaAngle);
}
void Tank::translate(sf::Vector2f delta) {
    position += delta;
    hull.translate(delta);
    trackA.translate(delta);
    trackB.translate(delta);
    gun.translate(delta);
}
void Tank::translate(float distance) {
    float rotation = hull.getRotation();
    float rotationDeg = rotation * M_PI / 180;
    float dx = -distance * sin(rotationDeg);
    float dy = distance * cos(rotationDeg);
    
    sf::Vector2f delta = {dx, dy};
    hull.translate(delta);
    trackA.translate(delta);
    trackB.translate(delta);
    gun.translate(delta);
    
    position += delta;
}

bool Tank::contains(sf::Vector2f point) const {
    bool hitHull = hull.contains(point);
    if (hitHull)
        std::cout << "X hull" << std::endl;
    bool hitGun = gun.contains(point);
    if (hitGun)
        std::cout << "X gun" << std::endl;
    bool hitTrackA = trackA.contains(point);
    if (hitTrackA)
        std::cout << "X track A" << std::endl;
    bool hitTrackB = trackB.contains(point);
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
