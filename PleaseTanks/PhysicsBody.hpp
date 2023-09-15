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
    void translate(sf::Vector2<float> delta);
    bool intersects(sf::Vector2<float> point);
    void connectToJoint(sf::Transform* jointTransform);
    sf::Vector2<float> position();
    
//    debug utils
    void draw(sf::RenderWindow& window);
    
private:
    sf::Transform getGlobalTransform();
};
