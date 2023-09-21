//
//  PhysicsBody.cpp
//  PleaseTanks
//
//  Created by Diniz Sá on 14/09/2023.
//

#include <array>
#include <cmath>
#include <algorithm>

#include "PhysicsBody.hpp"
#include "Utils.hpp"

int PhysicsBody::nextMaskId = 1;
std::vector<PhysicsBody*> PhysicsBody::allBodies;
int PhysicsBody::getAndIncrementMaskId() {
    return PhysicsBody::nextMaskId++;
}

void PhysicsBody::setCollisionMaskId(int groupId) {
    collisionMaskId = groupId;
}
void PhysicsBody::removeCollider() {
    allBodies.erase(std::remove(allBodies.begin(), allBodies.end(), this), allBodies.end());
}
PhysicsBody::PhysicsBody(sf::Vector2f size): hasMovementCollisions(false), collisionMaskId(0) {
    traveledDistance = 0.f;
    setSize(size);
    allBodies.push_back(this);
    
    sf::Vector2f leftTopPosition = -size/2.f;
    body.left = leftTopPosition.x;
    body.top = leftTopPosition.y;
}
PhysicsBody::~PhysicsBody() {
    removeCollider();
}

void PhysicsBody::setLocalRotationCenter(sf::Vector2f center) {
    localRotaionCenter = center;
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
bool PhysicsBody::translate(float delta, bool isTravel) {
    float rotationRadians = rotation() * M_PI / 180;
    float x = -delta * sin(rotationRadians);
    float y = delta * cos(rotationRadians);
    return translate({x, y}, isTravel);
}
bool PhysicsBody::translate(sf::Vector2f delta, bool isTravel) {
    body.left += delta.x;
    body.top += delta.y;
    
    if (collidedMovement()) {
        body.left -= delta.x;
        body.top -= delta.y;
        return false;
    }
    centerWorld = centerWorld() + delta;
    centerWorld.notify();
    
    if (isTravel) {
        traveledDistance = traveledDistance() + Utils::getLength(delta.x, delta.y);
        traveledDistance.notify();
    }
    return true;
}
bool PhysicsBody::rotate(float deltaAngle) {
    sf::Transform t;
    t.rotate(rotation());
    sf::Vector2f rotationOrigin = t.transformPoint(localRotaionCenter.x, localRotaionCenter.y);
    sf::Vector2f rotationCenter = centerWorld() + rotationOrigin;
    
    return rotateAroundOrigin(deltaAngle, rotationCenter);
}

bool PhysicsBody::rotateAroundOrigin(float deltaAngle, sf::Vector2f origin) {
    sf::Transform t0;
    t0.rotate(deltaAngle, origin);
    sf::Vector2f rotatedPosition = t0.transformPoint(centerWorld());

    rotation = rotation() + deltaAngle;
    if (!translate(rotatedPosition - centerWorld())) {
        rotation = rotation() - deltaAngle;
        return false;
    }
    rotation.notify();
    return true;
}

bool PhysicsBody::instersects(sf::Vector2f point) const {
    sf::Transform t;
    t.rotate(-rotation(), {body.left + body.width/2, body.top + body.height/2});
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
    t.rotate(rotation(), {body.left + body.width/2, body.top + body.height/2});
    for (auto& v : vertices) {
        v = t.transformPoint(v);
    }
    return vertices;
}
bool PhysicsBody::instersects(const PhysicsBody& other) const {
    float distance = Utils::getDistance(centerWorld(), other.centerWorld());
    if (distance > maxRadius + other.maxRadius) {
        return false;
    }
    
    std::array<sf::Vector2f, 4> vertices = getVertices();
    for (auto& v : vertices) {
        if (other.instersects(v)) {
            return true;
        }
    }
    
    std::array<sf::Vector2f, 4> verticesOther = other.getVertices();
    for (auto& v : verticesOther) {
        if (instersects(v)) {
            return true;
        }
    }
    
    return false;
}

bool PhysicsBody::collidedMovement() const {
    if (!hasMovementCollisions) {
        return false;
    }
    for (PhysicsBody* body : PhysicsBody::allBodies) {

        if (this->collisionMaskId != 0 && body->collisionMaskId == this->collisionMaskId)
            continue;
        
        if (!body->hasMovementCollisions)
            continue;

        if (this->instersects(*body)) {
            return true;
        }
    }
    return false;
}

void PhysicsBody::setMovementCollisions(bool hasCollisions) {
    hasMovementCollisions = hasCollisions;
}
float PhysicsBody::getTraveledDistance() {
    return traveledDistance();
}
