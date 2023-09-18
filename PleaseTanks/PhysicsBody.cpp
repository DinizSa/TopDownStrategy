//
//  PhysicsBody.cpp
//  PleaseTanks
//
//  Created by Diniz Sá on 14/09/2023.
//

#include <array>
#include <cmath>

#include "PhysicsBody.hpp"
#include "Utils.hpp"

PhysicsBody::PhysicsBody(sf::Vector2<float> size, sf::Vector2<float> position): centerPosition({0.f, 0.f}) {
    PhysicsBody::setSize(size);
    
    sf::Vector2<float> leftTopPosition = -size/2.f;
    body.left = leftTopPosition.x;
    body.top = leftTopPosition.y;
    
    PhysicsBody::translate(position);
}

void PhysicsBody::setDeltaCenter(sf::Vector2<float> deltaCenter) {
    this->deltaCenter = deltaCenter;
}
void PhysicsBody::setSize(sf::Vector2<float> size) {
    body.width = size.x;
    body.height = size.y;
    maxRadius = Utils::getLength(body.width/2.f, body.height/2.f);
}

sf::Vector2<float> PhysicsBody::getCenter() const {
    return centerPosition;
}
float PhysicsBody::getRotation() const {
    return rotation;
}
void PhysicsBody::rotate(float deltaAngle) {
    rotation += deltaAngle;
}
void PhysicsBody::translate(float delta) {
    float rotationRadians = rotation * M_PI / 180;
    float x = -delta * sin(rotationRadians);
    float y = delta * cos(rotationRadians);
    PhysicsBody::translate({x, y});
}
void PhysicsBody::translate(sf::Vector2<float> delta) {
    centerPosition += delta;
    body.left += delta.x;
    body.top += delta.y;
}
void PhysicsBody::rotateAroundParent(float currentAngle, float deltaAngle) {
    float rot0 = currentAngle;
    sf::Transform t0;
    t0.rotate(rot0, deltaCenter);
    auto p0 = t0.transformPoint(0.f, 0.f);

    sf::Transform t1;
    t1.rotate(rot0 + deltaAngle, deltaCenter);
    auto p1 = t1.transformPoint(0.f, 0.f);
    auto p2 = p1 - p0;

    PhysicsBody::rotate(deltaAngle);
    PhysicsBody::translate(p2);
}
bool PhysicsBody::contains(sf::Vector2<float> point) const {
    sf::Transform t;
    t.rotate(-rotation, centerPosition);
    sf::Vector2<float> rotatedPoint = t.transformPoint(point);
    return body.contains(rotatedPoint);
}
std::array<sf::Vector2<float>, 4> PhysicsBody::getVertices() const {
    std::array<sf::Vector2<float>, 4> vertices = {
        sf::Vector2<float>({body.left, body.top}),
        sf::Vector2<float>({body.left + body.width, body.top}),
        sf::Vector2<float>({body.left, body.top + body.height}),
        sf::Vector2<float>({body.left + body.width, body.top + body.height})
    };
    
    sf::Transform t;
    t.rotate(rotation, centerPosition);
    for (auto& v : vertices) {
        v = t.transformPoint(v);
    }
    return vertices;
}
bool PhysicsBody::contains(const PhysicsBody& other) const {
    float distance = Utils::getDistance(centerPosition, other.centerPosition);
    if (distance > maxRadius + other.maxRadius) {
        return false;
    }
    
    std::array<sf::Vector2<float>, 4> vertices = getVertices();
    for (auto& v : vertices) {
        if (other.contains(v)) {
            return true;
        }
    }
    
    std::array<sf::Vector2<float>, 4> verticesOther = other.getVertices();
    for (auto& v : verticesOther) {
        if (contains(v)) {
            return true;
        }
    }
    
    return false;
}
