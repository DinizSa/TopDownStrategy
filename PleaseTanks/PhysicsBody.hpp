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
protected:
    bool expired = false;
public:
    static std::vector<PhysicsBody*> allBodies;
    static void updatePhysicsBodys();
    bool isExpired();
    
private:
    bool hasMovementCollisions;
    sf::Vector2f velocity;
    sf::Vector2f lastPosition;
    float lastLocalRotation;
    bool shouldConsumePath;
    
protected:
    sf::FloatRect body;
    float localRotation;
    sf::Vector2f localRotationCenter;
    float maxRadius;
    Subject<float> rotation;
    Subject<sf::Vector2f> centerWorld;
    Subject<float> traveledDistance;
    Subject<bool> translating;
    Subject<bool> rotatingLocal;
    
    std::vector<sf::Vector2f> path;
    int collisionMaskId;
    float speed, angularSpeed;

private:
    bool collidedMovement() const;

protected:
    void removeCollider();
    std::array<sf::Vector2f, 4> getVertices() const;
    void setMovementCollisions(bool hasCollisions);
    float getTraveledDistance();

public:
    PhysicsBody(sf::Vector2f size);
    virtual ~PhysicsBody();
    virtual void update();
    
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
    virtual bool translateFront();
    virtual bool translateBack();
    virtual bool translate(sf::Vector2f delta, bool isTravel = true);
    virtual bool translate(float delta, bool isTravel = true);
    virtual bool rotateClock();
    virtual bool rotateAntiClock();
    virtual bool rotate(float deltaAngle);
    virtual bool rotate(float deltaAngle, sf::Vector2f origin);
    void travelToDestination(sf::Vector2f destination);
    void processPath();
    float getSpeed() const;
    void setSpeed(float speed);
    float getAngularSpeed() const;
    void setAngularSpeed(float angularSpeed);
    
    bool instersects(sf::Vector2f point) const;
    bool instersects(const PhysicsBody& other) const;
    std::vector<PhysicsBody*> getCollided() const;
    bool collidedAny() const;
    
    friend std::ostream& operator<<(std::ostream& os, const PhysicsBody& pb) {
        sf::Vector2f pos = pb.getCenter();
        sf::Vector2f size = pb.getSize();
        os << "[PhysicsBody] position: [" << pos.x << ", " << pos.y << "], size: [" << size.x << ", " << size.y << "], rotation: " << pb.getRotation() << std::endl;
        return os;
    }
};
