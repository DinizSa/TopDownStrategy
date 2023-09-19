//
//  PhysicsBody.hpp
//  PleaseTanks
//
//  Created by Diniz Sá on 14/09/2023.
//

#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>

#include "Subject.hpp"

class PhysicsBody {
    static std::vector<PhysicsBody*> allBodies;
    static int nextId;
    
private:
    bool collidedMovement() const;

protected:
    sf::FloatRect body;
    Subject<float> rotation;
    sf::Vector2f centerLocal;
    Subject<sf::Vector2f> centerWorld;
    float maxRadius;
    
    int id;
    bool movementCollisions;

public:
    PhysicsBody(sf::Vector2f size);
    
    static int getAndIncrementId();
    
    float getRotation() const;
    sf::Vector2f getCenter() const;
    void setSize(sf::Vector2f size);
    void setCenterLocal(sf::Vector2f centerLocal);
    
    bool translate(float delta);
    bool translate(sf::Vector2f delta);
    void rotate(float deltaAngle);
    void rotateAroundOrigin(float deltaAngle, sf::Vector2f origin);
    
    bool contains(sf::Vector2f point) const;
    bool contains(const PhysicsBody& other) const;
    
    void setId(int id);

protected:
    std::array<sf::Vector2f, 4> getVertices() const;
    void setMovementCollisions(bool hasCollisions);
};
