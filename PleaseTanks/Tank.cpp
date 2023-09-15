//
//  Tank.cpp
//  PleaseTanks
//
//  Created by Diniz Sá on 14/09/2023.
//
#include <SFML/Graphics.hpp>
#include <iostream>

#include "Tank.hpp"

Tank::Tank(sf::Vector2<float> position) : speed(5.f), angularSpeed(5.f), gunAngularSpeed(5.f), size({200.f, 200.f}), hull(size), PhysicsBody({position.x, position.y}, 70.f), tracks(size) {
    translate(std::move(position));
    hull.connectToJoint(&transform);
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

void Tank::rotateGun(bool clockwise) {
}
void Tank::rotateGunClock() {
}
void Tank::rotateGunAntiClock() {
}

void Tank::rotate(float degrees) {
    transform.rotate(degrees);
    hull.rotate(degrees);
    tracks.rotate(degrees);
}
void Tank::translate(sf::Vector2<float> delta) {
    transform.translate(delta.x, delta.y);
    hull.translate(delta);
    tracks.translate(delta);
}

void Tank::draw(sf::RenderWindow& window) {
    tracks.draw(window);
    hull.draw(window);
//    PhysicsBody::draw(window);
}
