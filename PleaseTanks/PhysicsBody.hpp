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
private:
    static std::vector<PhysicsBody*> allBodies;
    static int nextMaskId;
    
    bool hasMovementCollisions;
    sf::Vector2f velocity;
    
protected:
    sf::FloatRect body;
    Subject<float> rotation;
    sf::Vector2f localRotaionCenter;
    Subject<sf::Vector2f> centerWorld;
    float maxRadius;
    Subject<float> traveledDistance;
    int collisionMaskId; // ignore collisions of elements with the same mask id and different from zero

private:
    bool collidedMovement() const;
    void removeCollider();

protected:
    std::array<sf::Vector2f, 4> getVertices() const;
    void setMovementCollisions(bool hasCollisions);
    float getTraveledDistance();

public:
    PhysicsBody(sf::Vector2f size);
    virtual ~PhysicsBody();
    virtual void update(){};
    
    static int getAndIncrementMaskId();
    void setCollisionMaskId(int id);
    
    float getRotation() const;
    sf::Vector2f getCenter() const;
    void setSize(sf::Vector2f size);
    void setLocalRotationCenter(sf::Vector2f localRotaionCenter);

    void setVelocity(sf::Vector2f velocity);
    sf::Vector2f getVelocity();
    bool applyVelocity();
    bool translate(float delta, bool isTravel = true);
    bool translate(sf::Vector2f delta, bool isTravel = true);
    bool rotate(float deltaAngle);
    bool rotateAroundOrigin(float deltaAngle, sf::Vector2f origin);
    
    bool instersects(sf::Vector2f point) const;
    bool instersects(const PhysicsBody& other) const;
    std::vector<PhysicsBody*> getCollided() const;
};
