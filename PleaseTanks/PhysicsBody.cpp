//
//  PhysicsBody.cpp
//  PleaseTanks
//
//  Created by Diniz Sá on 14/09/2023.
//

#include "PhysicsBody.hpp"
#include <cmath>

PhysicsBody::PhysicsBody(sf::Vector2<float> size, sf::Vector2<float> position, sf::Vector2<float> deltaCenter): deltaCenter(deltaCenter), centerPosition({0.f, 0.f}) {
    body.width = size.x;
    body.height = size.y;
    
    sf::Vector2<float> leftTopPosition = -size/2.f;
    body.left = leftTopPosition.x;
    body.top = leftTopPosition.y;
    
    translate(position);
    
    std::cout << "centerPosition: " << centerPosition.x << ", " << centerPosition.y << std::endl;
}

sf::Vector2<float> PhysicsBody::getCenter() const {
    return centerPosition;
}
float PhysicsBody::getRotation() const {
    return rotation;
}
const sf::FloatRect& PhysicsBody::getBody() const {
    return body;
}
void PhysicsBody::rotate(float deltaAngle) {
    rotation += deltaAngle;
}
void PhysicsBody::translate(float delta) {
    float rotationRadians = rotation * M_PI / 180;
    float x = -delta * sin(rotationRadians);
    float y = delta * cos(rotationRadians);
    translate({x, y});
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

    rotate(deltaAngle);
    translate(p2);
}
bool PhysicsBody::contains(sf::Vector2<float> point) const {
    sf::Transform t;
    t.rotate(-rotation, centerPosition);
    sf::Vector2<float> rotatedPoint = t.transformPoint(point);
    return body.contains(rotatedPoint);
}
bool PhysicsBody::contains(const PhysicsBody& other) const {
//    const sf::FloatRect otherBody = other.getBody();
//    float otherRotation = other.getRotation();
//    sf::Vector2<float> otherCenter = other.getWorldCenter();
//    
//    float p0, p1, p2, p3;
//    sf::Transform t;
//    t.rotate(-otherRotation, {body.width/2.f, body.height/2.f});
    
    return true;
}
