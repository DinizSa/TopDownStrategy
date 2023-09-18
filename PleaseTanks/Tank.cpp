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

Tank::Tank(sf::Vector2<float> size, sf::Vector2<float> position) : position(position), speed(5.f), angularSpeed(5.f), size(size), hull(size, position), gun(size, position), trackA({size.x/4, size.y}, position), trackB({size.x/4, size.y}, position) {
    trackA.setDeltaCenter({(2.f/10.f) * size.x, 0});
    trackB.setDeltaCenter({(-2.f/10.f) * size.x, 0});
}
Tank::~Tank() {
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
    auto currentRotation = hull.getRotation();
    trackA.rotateAroundParent(currentRotation, deltaAngle);
    trackB.rotateAroundParent(currentRotation, deltaAngle);
    gun.rotateAroundParent(currentRotation, deltaAngle);
    hull.rotate(deltaAngle);
}
void Tank::translate(sf::Vector2<float> delta) {
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
    
    sf::Vector2<float> delta = {dx, dy};
    hull.translate(delta);
    trackA.translate(delta);
    trackB.translate(delta);
    gun.translate(delta);
    
    position += delta;
}

void Tank::draw(sf::RenderWindow& window) {
    trackA.draw(window);
    trackB.draw(window);
    hull.draw(window);
    gun.draw(window);
}
