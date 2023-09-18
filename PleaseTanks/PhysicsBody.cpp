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

PhysicsBody::PhysicsBody(sf::Vector2f size) {
    setSize(size);
    
    sf::Vector2f leftTopPosition = -size/2.f;
    body.left = leftTopPosition.x;
    body.top = leftTopPosition.y;
}

void PhysicsBody::setCenterLocal(sf::Vector2f center) {
    centerLocal = center;
}
void PhysicsBody::setSize(sf::Vector2f size) {
    body.width = size.x;
    body.height = size.y;
    maxRadius = Utils::getLength(body.width/2.f, body.height/2.f);
}

sf::Vector2f PhysicsBody::getCenter() const {
    return centerWorld();
}
float PhysicsBody::getRotation() const {
    return rotation();
}
void PhysicsBody::translate(float delta) {
    float rotationRadians = rotation() * M_PI / 180;
    float x = -delta * sin(rotationRadians);
    float y = delta * cos(rotationRadians);
    translate({x, y});
}
void PhysicsBody::translate(sf::Vector2f delta) {
    centerWorld = centerWorld() + delta;
    body.left += delta.x;
    body.top += delta.y;
}
void PhysicsBody::rotate(float deltaAngle) {
    sf::Transform t;
    t.rotate(rotation());
    sf::Vector2f rotationOrigin = t.transformPoint(centerLocal.x, centerLocal.y);
    sf::Vector2f rotationCenter = centerWorld() + rotationOrigin;
    
    rotateAroundOrigin(deltaAngle, rotationCenter);
}

void PhysicsBody::rotateAroundOrigin(float deltaAngle, sf::Vector2f origin) {
    sf::Transform t0;
    t0.rotate(deltaAngle, origin);
    sf::Vector2f rotatedPosition = t0.transformPoint(centerWorld());

    rotation = rotation() + deltaAngle;
    translate(rotatedPosition - centerWorld());
}
bool PhysicsBody::contains(sf::Vector2f point) const {
    sf::Transform t;
    t.rotate(-rotation(), centerWorld());
    sf::Vector2f rotatedPoint = t.transformPoint(point);
    return body.contains(rotatedPoint);
}
std::array<sf::Vector2f, 4> PhysicsBody::getVertices() const {
    std::array<sf::Vector2f, 4> vertices = {
        sf::Vector2f({body.left, body.top}),
        sf::Vector2f({body.left + body.width, body.top}),
        sf::Vector2f({body.left, body.top + body.height}),
        sf::Vector2f({body.left + body.width, body.top + body.height})
    };
    
    sf::Transform t;
    t.rotate(rotation(), centerWorld());
    for (auto& v : vertices) {
        v = t.transformPoint(v);
    }
    return vertices;
}
bool PhysicsBody::contains(const PhysicsBody& other) const {
    float distance = Utils::getDistance(centerWorld(), other.centerWorld());
    if (distance > maxRadius + other.maxRadius) {
        return false;
    }
    
    std::array<sf::Vector2f, 4> vertices = getVertices();
    for (auto& v : vertices) {
        if (other.contains(v)) {
            return true;
        }
    }
    
    std::array<sf::Vector2f, 4> verticesOther = other.getVertices();
    for (auto& v : verticesOther) {
        if (contains(v)) {
            return true;
        }
    }
    
    return false;
}
