//
//  PhysicsBody.hpp
//  PleaseTanks
//
//  Created by Diniz Sá on 14/09/2023.
//

#pragma once

#include <SFML/Graphics.hpp>

class PhysicsBody {
protected:
    sf::CircleShape circleShape;
    sf::Color debugColor;
    sf::Transform transform;
    sf::Transform* jointTransform;
    
public:
    PhysicsBody(sf::Vector2<float> position, float radius);
    sf::Vector2<float> position();
    virtual void translate(sf::Vector2<float> delta);
    virtual void rotate(float degrees);
    virtual void rotateWithCenter(float degrees, sf::Vector2<float> center);
    bool intersects(sf::Vector2<float> point);
    void connectToJoint(sf::Transform* jointTransform);
    
//    debug utils
    void draw(sf::RenderWindow& window);
    
private:
    sf::Transform getGlobalTransform();
};
