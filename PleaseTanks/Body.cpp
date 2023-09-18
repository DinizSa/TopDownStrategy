//
//  Hull.cpp
//  PleaseTanks
//
//  Created by Diniz Sá on 14/09/2023.
//

#include "Body.hpp"

Body::Body(sf::Vector2<float> size, sf::Vector2<float> position, const std::string&& texturePath) :
    Drawable(size, position, std::move(texturePath)),
    PhysicsBody(size, position)
{}

void Body::setDeltaCenter(sf::Vector2<float> deltaCenter) {
    Drawable::setDeltaCenter(deltaCenter);
    PhysicsBody::setDeltaCenter(deltaCenter);
}
void Body::rotate(float deltaAngle) {
    Drawable::rotate(deltaAngle);
    PhysicsBody::rotate(deltaAngle);
}
void Body::translate(float distance) {
    Drawable::translate(distance);
    PhysicsBody::translate(distance);
}
void Body::translate(sf::Vector2<float> delta) {
    Drawable::translate(delta);
    PhysicsBody::translate(delta);
}
void Body::rotateAroundParent(float currentAngle, float deltaAngle) {
    Drawable::rotateAroundParent(currentAngle, deltaAngle);
    PhysicsBody::rotateAroundParent(currentAngle, deltaAngle);
}
