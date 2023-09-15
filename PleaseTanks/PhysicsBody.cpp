//
//  PhysicsBody.cpp
//  PleaseTanks
//
//  Created by Diniz Sá on 14/09/2023.
//

#include <cmath>

#include "PhysicsBody.hpp"

PhysicsBody::PhysicsBody(sf::Vector2<float> position, float radius): debugColor(sf::Color(255,0,0,255)), jointTransform(nullptr) {
    translate(position);
    circleShape.setFillColor(debugColor);
    circleShape.setRadius(radius);
    circleShape.setOrigin(radius, radius);
}

void PhysicsBody::connectToJoint(sf::Transform* jointTransform) {
    this->jointTransform = jointTransform;
}


void PhysicsBody::translate(sf::Vector2<float> delta) {
    transform.translate(delta.x, delta.y);
}

sf::Vector2<float> PhysicsBody::position() {
    return getGlobalTransform().transformPoint(0.f, 0.f);
}

bool PhysicsBody::intersects(sf::Vector2<float> point) {
    sf::Vector2<float> pos =  position();
    float radius = circleShape.getRadius();
    sf::Vector2<float> delta = pos - point;
    return sqrt(delta.x * delta.x + delta.y * delta.y) < radius;
}

sf::Transform PhysicsBody::getGlobalTransform() {
    if (jointTransform != nullptr) {
        return jointTransform->combine(transform);
    }
    return transform;
}


//    debug utils
void PhysicsBody::draw(sf::RenderWindow& window) {
    window.draw(circleShape, getGlobalTransform());
}
