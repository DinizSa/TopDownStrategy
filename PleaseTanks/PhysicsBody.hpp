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
    float traveledDistance;

public:
    PhysicsBody(sf::Vector2f size);
    
    static int getAndIncrementId();
    
    float getRotation() const;
    sf::Vector2f getCenter() const;
    void setSize(sf::Vector2f size);
    void setCenterLocal(sf::Vector2f centerLocal);
    
    bool translate(float delta);
    virtual bool translate(sf::Vector2f delta);
    bool rotate(float deltaAngle);
    bool rotateAroundOrigin(float deltaAngle, sf::Vector2f origin);
    
    bool instersects(sf::Vector2f point) const;
    bool instersects(const PhysicsBody& other) const;
    
    void setId(int id);

protected:
    std::array<sf::Vector2f, 4> getVertices() const;
    void setMovementCollisions(bool hasCollisions);
};
