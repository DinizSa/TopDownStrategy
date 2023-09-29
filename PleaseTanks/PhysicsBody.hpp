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
    static int nextMaskId;
    static std::vector<PhysicsBody*> updatables;
protected:
    static void addUpdatable(PhysicsBody* physicBody);
    static void removeUpdatable(PhysicsBody* physicBody);
    bool expired = false;
public:
    static std::vector<PhysicsBody*> allBodies;
    static void updatePhysicsBodys();
    bool isExpired();
    
private:
    bool hasMovementCollisions;
    sf::Vector2f velocity;
    
protected:
    sf::FloatRect body;
    Subject<float> rotation;
    sf::Vector2f localRotationCenter;
    Subject<sf::Vector2f> centerWorld;
    float maxRadius;
    Subject<float> traveledDistance;
    
    std::vector<sf::Vector2f> destinations;
    int collisionMaskId;

private:
    bool collidedMovement() const;
    void removeCollider();

protected:
    std::array<sf::Vector2f, 4> getVertices() const;
    void setMovementCollisions(bool hasCollisions);
    float getTraveledDistance();

public:
    void setPath(std::vector<sf::Vector2f> pathPoints);
    PhysicsBody(sf::Vector2f size);
    virtual ~PhysicsBody();
    virtual void update();
    
    virtual void receiveDamage(int damage){};
    
    static int getAndIncrementMaskId();
    void setCollisionMaskId(int id);
    
    float getRotation() const;
    bool getMovementCollisions() const;
    int getCollisionMaskId() const;
    sf::Vector2f getCenter() const;
    float getRadius() const;
    sf::Vector2f getSize() const;
    void setSize(sf::Vector2f size);
    void setLocalRotationCenter(sf::Vector2f localRotationCenter);

    void setVelocity(sf::Vector2f velocity);
    void setVelocityAndRotate(sf::Vector2f velocity);
    sf::Vector2f getVelocity();
    bool applyVelocity();
    bool translate(sf::Vector2f delta, bool isTravel = true);
    bool rotate(float deltaAngle);
    bool rotateAroundOrigin(float deltaAngle, sf::Vector2f origin);
    
    bool instersects(sf::Vector2f point) const;
    bool instersects(const PhysicsBody& other) const;
    std::vector<PhysicsBody*> getCollided() const;
    bool collidedAny() const;
};
