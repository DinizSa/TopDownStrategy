//
//  PhysicsBody.cpp
//  PleaseTanks
//
//  Created by Diniz Sá on 14/09/2023.
//

#include <cmath>
#include <iostream>

#include "PhysicsBody.hpp"

PhysicsBody::PhysicsBody(sf::Vector2<float> position, sf::Vector2<float> size, sf::Vector2<float> origin): origin(origin), debugColor(sf::Color(255,0,0,140)) {
    translate(position);
    rect.setFillColor(debugColor);
    rect.setSize(size);
    rect.setOrigin(size.x/2, size.y/2);
}

// Local transform operations
void PhysicsBody::rotate(float degrees) {
    rect.rotate(degrees);
}
void PhysicsBody::rotateWithCenter(float degrees, sf::Vector2<float> center) {
    localTransform.rotate(degrees, center);
}
void PhysicsBody::translate(sf::Vector2<float> delta) {
    delta += rect.getPosition();
    rect.setPosition(delta);
}

bool PhysicsBody::intersects(sf::Vector2<float> point) {
//    sf::Vector2<float> pos =  rect.getPosition();
//    sf::Vector2<float> delta = pos - point;
//    return sqrt(delta.x * delta.x + delta.y * delta.y) < radius;
    return true;
}

//    debug utils
void PhysicsBody::draw(sf::RenderWindow& window) {
    window.draw(rect, localTransform);
}
