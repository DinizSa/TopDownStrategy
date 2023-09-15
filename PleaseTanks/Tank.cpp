//
//  Tank.cpp
//  PleaseTanks
//
//  Created by Diniz Sá on 14/09/2023.
//
#include <SFML/Graphics.hpp>
#include <iostream>

#include "Tank.hpp"

Tank::Tank(sf::Vector2<float> position) : speed(5.f), angularSpeed(5.f), gunAngularSpeed(5.f), size({200.f, 200.f}), hull(size), tracks(size), gun(position) {
    translate(std::move(position));
}
Tank::~Tank() {
}
void Tank::moveFront() {
    translate({0.f, -speed});
}
void Tank::moveBack() {
    translate({0.f, speed});
}

void Tank::rotateClock() {
    rotate(angularSpeed);
}
void Tank::rotateAntiClock() {
    rotate(-angularSpeed);
}

void Tank::rotateGun(float degrees) {
}
void Tank::rotateGunClock() {
    gun.rotateLocal(gunAngularSpeed);
}
void Tank::rotateGunAntiClock() {
    gun.rotateLocal(-gunAngularSpeed);
}

void Tank::rotate(float degrees) {
    hull.rotateWorld(degrees);
    tracks.rotate(degrees);
    gun.rotateWorld(degrees);
}
void Tank::translate(sf::Vector2<float> delta) {
    hull.translateWorld(delta);
    tracks.translate(delta);
    gun.translateWorld(delta);
}

void Tank::draw(sf::RenderWindow& window) {
    tracks.draw(window);
    hull.draw(window);
    gun.draw(window);
//    PhysicsBody::draw(window);
}
