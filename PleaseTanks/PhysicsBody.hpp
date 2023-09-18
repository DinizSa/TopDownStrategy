//
//  PhysicsBody.hpp
//  PleaseTanks
//
//  Created by Diniz Sá on 14/09/2023.
//

#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

#include "Subject.hpp"

class PhysicsBody {
protected:
    sf::FloatRect body;
    Subject<float> rotation;
    sf::Vector2<float> deltaCenter;
    Subject<sf::Vector2<float>> centerPosition;
    float maxRadius;

public:
    PhysicsBody(sf::Vector2<float> size, sf::Vector2<float> position);

    float getRotation() const;
    sf::Vector2<float> getCenter() const;
    virtual void setSize(sf::Vector2<float> size);
    virtual void setDeltaCenter(sf::Vector2<float> deltaCenter);
    
    virtual void translate(float delta);
    virtual void translate(sf::Vector2<float> delta);
//    virtual void setRotationCenter(sf::Vector2<float>&& center);
    virtual void rotate(float deltaAngle);
    virtual void rotateAroundParent(float currentAngle, float degrees);
    
    bool contains(sf::Vector2<float> point) const;
    bool contains(const PhysicsBody& other) const;

protected:
    std::array<sf::Vector2<float>, 4> getVertices() const;
};
