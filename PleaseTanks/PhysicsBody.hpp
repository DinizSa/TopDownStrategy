//
//  PhysicsBody.hpp
//  PleaseTanks
//
//  Created by Diniz Sá on 14/09/2023.
//

#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class PhysicsBody {
protected:
    sf::FloatRect body;
    float rotation;
    sf::Vector2<float> deltaCenter;
    sf::Vector2<float> centerPosition;
    float maxRadius;
    
public:
    PhysicsBody(sf::Vector2<float> size, sf::Vector2<float> position, sf::Vector2<float> deltaCenter);
    
    const sf::FloatRect& getBody() const;
    float getRotation() const;
    sf::Vector2<float> getCenter() const;
    void setSize(sf::Vector2<float> size);
    
    void translate(float delta);
    void translate(sf::Vector2<float> delta);
    void setRotationCenter(sf::Vector2<float>&& center);
    void rotate(float deltaAngle);
    virtual void rotateAroundParent(float currentAngle, float degrees);
    bool contains(sf::Vector2<float> point) const;
    bool contains(const PhysicsBody& other) const;
    
protected:
    std::array<sf::Vector2<float>, 4> getVertices() const;
};
