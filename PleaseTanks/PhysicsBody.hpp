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
    sf::Vector2f centerLocal;
    Subject<sf::Vector2f> centerWorld;
    float maxRadius;
    
//    static std::vector<PhysicsBody*> allBodies;

public:
    PhysicsBody(sf::Vector2f size);

    float getRotation() const;
    sf::Vector2f getCenter() const;
    void setSize(sf::Vector2f size);
    void setCenterLocal(sf::Vector2f centerLocal);
    
    void translate(float delta);
    void translate(sf::Vector2f delta);
    void rotate(float deltaAngle);
    void rotateAroundOrigin(float deltaAngle, sf::Vector2f origin);
    
    bool contains(sf::Vector2f point) const;
    bool contains(const PhysicsBody& other) const;

protected:
    std::array<sf::Vector2f, 4> getVertices() const;
};
