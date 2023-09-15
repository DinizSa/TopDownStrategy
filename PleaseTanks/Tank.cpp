//
//  Tank.cpp
//  PleaseTanks
//
//  Created by Diniz Sá on 14/09/2023.
//
#include <SFML/Graphics.hpp>
#include <iostream>

#include "Tank.hpp"

Tank::Tank(sf::Vector2<float> position) : speed(5.f), angularSpeed(5.f), gunAngularSpeed(5.f), size({200.f, 200.f}), hull({200.f, 200.f}), PhysicsBody({position.x, position.y}, 70.f) {
    move(std::move(position));
    hull.connectToJoint(&transform);
}
Tank::~Tank() {
}
void Tank::move(sf::Vector2<float>&& delta) {
    transform.translate(delta.x, delta.y);
}
void Tank::moveFront() {
    move({0.f, -speed});
}
void Tank::moveBack() {
    move({0.f, speed});
}

void Tank::rotateClock() {
    transform.rotate(angularSpeed);
}
void Tank::rotateAntiClock() {
    transform.rotate(-angularSpeed);
}

void Tank::rotateGun(bool clockwise) {
    
}
void Tank::rotateGunClock() {
    
}
void Tank::rotateGunAntiClock() {
    
}

void Tank::draw(sf::RenderWindow& window) {
    hull.draw(window, &transform);
//    PhysicsBody::draw(window);
}
