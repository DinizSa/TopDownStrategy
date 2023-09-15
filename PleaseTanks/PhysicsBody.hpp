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
    sf::Transform localTransform;
    sf::Transform worldTransform;
    sf::Transform combinedTransform;
    
public:
    PhysicsBody(sf::Vector2<float> position, float radius);
    sf::Vector2<float> position();
    virtual void translateLocal(sf::Vector2<float> delta);
    virtual void rotateLocal(float degrees);
    virtual void rotateWithCenterLocal(float degrees, sf::Vector2<float> center);
    virtual void translateWorld(sf::Vector2<float> delta);
    virtual void rotateWorld(float degrees);
    virtual void rotateWithCenterWorld(float degrees, sf::Vector2<float> center);
    bool intersects(sf::Vector2<float> point);
    
//    debug utils
    void draw(sf::RenderWindow& window);
    
private:
    void updateCombinedTransform();
};
