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

Tank::Tank(sf::Vector2<float> position) : speed(5.f), angularSpeed(5.f), gunAngularSpeed(10.f), size({200.f, 200.f}), hull(size), gun(position), trackA({size.x/4, size.y}, {(2.f/10.f) * size.x, 0}), trackB({size.x/4, size.y}, {(-2.f/10.f) * size.x, 0}) {
    translate(std::move(position));
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
    gun.rotate(gunAngularSpeed);
}
void Tank::rotateGunAntiClock() {
    gun.rotate(-gunAngularSpeed);
}

void Tank::rotate(float degrees) {
    auto rot = hull.getRotation();
    trackA.rotateAroundParent(degrees, degrees);
    trackB.rotateAroundParent(degrees, degrees);
    gun.rotateAroundParent(rot, degrees);
    hull.rotate(degrees);
}
void Tank::translate(sf::Vector2<float> delta) {
    position += delta;
    hull.translate(delta);
    trackA.translate(delta);
    trackB.translate(delta);
    gun.translate(delta);
}
void Tank::translate(float distance) {
    float rotation = hull.getRotation(); // TODO: save rotation in this class?
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
