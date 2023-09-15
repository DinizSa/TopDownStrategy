//
//  PhysicsBody.cpp
//  PleaseTanks
//
//  Created by Diniz Sá on 14/09/2023.
//

#include <cmath>
#include <iostream>

#include "PhysicsBody.hpp"

PhysicsBody::PhysicsBody(sf::Vector2<float> position, float radius): debugColor(sf::Color(255,0,0,140)) {
    translateWorld(position);
    circleShape.setFillColor(debugColor);
    circleShape.setRadius(radius);
    circleShape.setOrigin(radius, radius);
}

// Local transform operations
void PhysicsBody::rotateLocal(float degrees) {
    localTransform.rotate(degrees, position());
    updateCombinedTransform();
}
void PhysicsBody::rotateWithCenterLocal(float degrees, sf::Vector2<float> center) {
    localTransform.rotate(degrees, center);
    updateCombinedTransform();
}
void PhysicsBody::translateLocal(sf::Vector2<float> delta) {
    localTransform.translate(delta.x, delta.y);
    updateCombinedTransform();
}

// World transform operations
void PhysicsBody::rotateWorld(float degrees) {
    worldTransform.rotate(degrees);
    updateCombinedTransform();
}
void PhysicsBody::rotateWithCenterWorld(float degrees, sf::Vector2<float> center) {
    worldTransform.rotate(degrees, center);
    updateCombinedTransform();
}
void PhysicsBody::translateWorld(sf::Vector2<float> delta) {
    worldTransform.translate(delta.x, delta.y);
    updateCombinedTransform();
}

void PhysicsBody::updateCombinedTransform() {
    combinedTransform = localTransform * worldTransform;
}

sf::Vector2<float> PhysicsBody::position() {
    return combinedTransform.transformPoint(0.f, 0.f);
}

bool PhysicsBody::intersects(sf::Vector2<float> point) {
    sf::Vector2<float> pos =  position();
    float radius = circleShape.getRadius();
    sf::Vector2<float> delta = pos - point;
    return sqrt(delta.x * delta.x + delta.y * delta.y) < radius;
}

//    debug utils
void PhysicsBody::draw(sf::RenderWindow& window) {
    window.draw(circleShape, combinedTransform);
}
