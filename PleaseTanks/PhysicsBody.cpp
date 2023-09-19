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

int PhysicsBody::nextId = 0;
std::vector<PhysicsBody*> PhysicsBody::allBodies;
int PhysicsBody::getAndIncrementId() {
    return PhysicsBody::nextId++;
}

void PhysicsBody::setId(int id) {
    this->id = id;
    allBodies.push_back(this);
}
PhysicsBody::PhysicsBody(sf::Vector2f size): movementCollisions(false) {
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
bool PhysicsBody::translate(float delta) {
    float rotationRadians = rotation() * M_PI / 180;
    float x = -delta * sin(rotationRadians);
    float y = delta * cos(rotationRadians);
    return translate({x, y});
}
bool PhysicsBody::translate(sf::Vector2f delta) {
    body.left += delta.x;
    body.top += delta.y;
    
    if (collidedMovement()) {
        body.left -= delta.x;
        body.top -= delta.y;
        return false;
    }
    centerWorld = centerWorld() + delta;
    return true;
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
    t.rotate(-rotation(), {body.left + body.width/2, body.top + body.height/2});
//    t.rotate(-rotation(), centerWorld());
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
//    float halfSizeX = body.width/2.f;
//    float halfSizeY = body.height/2.f;
//    sf::Vector2f pos = centerWorld();
//
//    std::array<sf::Vector2f, 4> vertices = {
//        sf::Vector2f({pos.x - halfSizeX, pos.y - halfSizeY}),
//        sf::Vector2f({pos.x + halfSizeX, pos.y - halfSizeY}),
//        sf::Vector2f({pos.x - halfSizeX, pos.y + halfSizeY}),
//        sf::Vector2f({pos.x + halfSizeX, pos.y + halfSizeY})
//    };
    
    sf::Transform t;
    t.rotate(rotation(), {body.left + body.width/2, body.top + body.height/2});
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

bool PhysicsBody::collidedMovement() const {
    if (!movementCollisions) {
        return false;
    }
    for (PhysicsBody* body : PhysicsBody::allBodies) {
        if (body->id == this->id)
            continue;
        
        if (!body->movementCollisions)
            continue;

        if (this->contains(*body)) {
            return true;
        }
    }
    return false;
}

void PhysicsBody::setMovementCollisions(bool hasCollisions) {
    movementCollisions = hasCollisions;
}
