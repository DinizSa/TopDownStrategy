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

void PhysicsBody::updatePhysicsBodys() {
    for (auto it = PhysicsBody::allBodies.begin(); it != PhysicsBody::allBodies.end();) {
        PhysicsBody* physicsBody = *it;
        if (physicsBody->isExpired()) {
            delete physicsBody;
        } else {
            ++it;
        }
    }
    
    for (auto physicsBody : PhysicsBody::allBodies) {
        physicsBody->update();
    }
}
void PhysicsBody::removeCollider() {
    allBodies.erase(std::remove(PhysicsBody::allBodies.begin(), PhysicsBody::allBodies.end(), this), PhysicsBody::allBodies.end());
}
bool PhysicsBody::isExpired() {
    return expired;
}


int PhysicsBody::nextMaskId = 1;
std::vector<PhysicsBody*> PhysicsBody::allBodies;
int PhysicsBody::getAndIncrementMaskId() {
    return PhysicsBody::nextMaskId++;
}
void PhysicsBody::update() {
    processPath();
    applyVelocity();
    
    if (translating() && lastPosition == centerWorld()) {
        translating = false;
        translating.notify();
    }
    lastPosition = centerWorld();
    
    if (rotatingLocal() && lastLocalRotation == localRotation) {
        rotatingLocal = false;
        rotatingLocal.notify();
    }
    lastLocalRotation = localRotation;
}
void PhysicsBody::processPath() {
    if (path.size() == 0)
        return ;

    sf::Vector2f destination = path[path.size() - 1];
    if (shouldConsumePath) {
        sf::Vector2f deltaPos = destination - centerWorld();
        
        sf::Vector2f unitVelocity = deltaPos / sqrt((deltaPos.x * deltaPos.x) + (deltaPos.y * deltaPos.y));
        sf::Vector2f vel = unitVelocity * speed;
        setVelocityAndRotate(vel);
        shouldConsumePath = false;
    }
    if (Utils::getDistance(centerWorld(), destination) < (maxRadius / 2.f)) {
        path.pop_back();
        
        if (path.size() == 0) {
            setVelocity({0.f, 0.f});
        } else {
            shouldConsumePath = true;
        }
    }
}
float PhysicsBody::getSpeed() const {
    return speed;
}
void PhysicsBody::setSpeed(float newSpeed) {
    speed = newSpeed;
}
float PhysicsBody::getAngularSpeed() const {
    return speed;
}
void PhysicsBody::setAngularSpeed(float newAngularSpeed) {
    angularSpeed = newAngularSpeed;
}
void PhysicsBody::setCollisionMaskId(int groupId) {
    collisionMaskId = groupId;
}
PhysicsBody::PhysicsBody(sf::Vector2f size): hasMovementCollisions(false), collisionMaskId(0), velocity({0.f, 0.f}), localRotation(0.f), speed(0.f), angularSpeed(0.f), shouldConsumePath(false), lastLocalRotation(0.f) {
    traveledDistance = 0.f;
    setSize(size);
    allBodies.push_back(this);
    
    sf::Vector2f leftTopPosition = -size/2.f;
    body.left = leftTopPosition.x;
    body.top = leftTopPosition.y;
    translating = false;
    rotatingLocal = false;
}
PhysicsBody::~PhysicsBody() {
    removeCollider();
}

void PhysicsBody::setLocalRotationCenter(sf::Vector2f center) {
    localRotationCenter = center;
}
void PhysicsBody::setSize(sf::Vector2f size) {
    body.width = size.x;
    body.height = size.y;
    maxRadius = Utils::getLength(body.width/2.f, body.height/2.f);
}
void PhysicsBody::travelToDestination(sf::Vector2f destination) {
    path = Utils::getPathPoints(this, destination);
    shouldConsumePath = true;
}
int PhysicsBody::getCollisionMaskId() const {
    return collisionMaskId;
}
sf::Vector2f PhysicsBody::getCenter() const {
    return centerWorld();
}
sf::Vector2f PhysicsBody::getSize() const {
    return {body.width, body.height};
}
float PhysicsBody::getRadius() const {
    return maxRadius;
}
bool PhysicsBody::getMovementCollisions() const {
    return hasMovementCollisions;
}
float PhysicsBody::getRotation() const {
    return rotation();
}

void PhysicsBody::setVelocity(sf::Vector2f v) {
    velocity = v;
}
void PhysicsBody::setVelocityAndRotate(sf::Vector2f v) {
    float imagesInitialAngle = 90.f;
    
    float velocityAngle = Utils::getAngle(v);
    float currentRot = rotation();
    float angle = imagesInitialAngle + velocityAngle - currentRot;
    rotate(angle);

    setVelocity(v);
}
sf::Vector2f PhysicsBody::getVelocity() {
    return velocity;
}
bool PhysicsBody::applyVelocity() {
    float dV = Utils::getLength(velocity);
    if (dV > 0.001f) {
        return translate(velocity, true);
    }
    return false;
}
bool PhysicsBody::translate(float delta, bool isTravel) {
    
    float rot = getRotation();
    float rotationDeg = rot * M_PI / 180;
    float dx = -delta * sin(rotationDeg);
    float dy = delta * cos(rotationDeg);
    
    sf::Vector2f deltaPos = {dx, dy};
    
    return translate(deltaPos, isTravel);
}
bool PhysicsBody::translate(sf::Vector2f delta, bool isTravel) {
    if (isTravel) {
        traveledDistance = traveledDistance() + Utils::getLength(delta);
        traveledDistance.notify();
    }
    body.left += delta.x;
    body.top += delta.y;
    
    if (collidedMovement()) {
        body.left -= delta.x;
        body.top -= delta.y;
        return false;
    }
    centerWorld = centerWorld() + delta;
    centerWorld.notify();
    
    
    if (isTravel && !translating()) {
        translating = true;
        translating.notify();
    }
    
    return true;
}
bool PhysicsBody::translateFront() {
    return translate(-speed);
}
bool PhysicsBody::translateBack() {
    return translate(speed);
}
bool PhysicsBody::rotateClock() {
    return rotate(angularSpeed);
}
bool PhysicsBody::rotateAntiClock() {
    return rotate(-angularSpeed);
}
bool PhysicsBody::rotate(float deltaAngle) {
    sf::Transform t;
    t.rotate(rotation());
    sf::Vector2f rotationOrigin = t.transformPoint(localRotationCenter.x, localRotationCenter.y);
    sf::Vector2f rotationCenter = centerWorld() + rotationOrigin;
    
    bool success = rotate(deltaAngle, rotationCenter);
    if (success) {
        localRotation += deltaAngle;
        
        if (!rotatingLocal()) {
            rotatingLocal = true;
            rotatingLocal.notify();
        }
    }
    return success;
}

bool PhysicsBody::rotate(float deltaAngle, sf::Vector2f origin) {
    sf::Transform t0;
    t0.rotate(deltaAngle, origin);
    sf::Vector2f rotatedPosition = t0.transformPoint(centerWorld());

    rotation = remainder(rotation() + deltaAngle, 360.f);
    if (!translate(rotatedPosition - centerWorld(), false)) {
        rotation = remainder(rotation() - deltaAngle, 360.f);
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

bool PhysicsBody::collidedAny() const {
    for (PhysicsBody* body : PhysicsBody::allBodies) {
        
        if (this == body)
            continue;
        
        if (!body->hasMovementCollisions)
            continue;

        if (this->collisionMaskId != 0 && body->collisionMaskId == this->collisionMaskId)
            continue;

        if (this->instersects(*body)) {
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
        
        if (this == body)
            continue;

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
std::vector<PhysicsBody*> PhysicsBody::getCollided() const {
    std::vector<PhysicsBody*> collided;
    
    for (PhysicsBody* body : PhysicsBody::allBodies) {
        
        if (this == body)
            continue;
        
        if (this->collisionMaskId != 0 && body->collisionMaskId == this->collisionMaskId)
            continue;

        if (this->instersects(*body)) {
            collided.push_back(body);
        }
    }
    return collided;
}

void PhysicsBody::setMovementCollisions(bool hasCollisions) {
    hasMovementCollisions = hasCollisions;
}
float PhysicsBody::getTraveledDistance() {
    return traveledDistance();
}
