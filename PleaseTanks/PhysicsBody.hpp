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
    sf::RectangleShape rect;
    sf::Color debugColor;
    sf::Transform localTransform;
    sf::Vector2<float> origin;
    
public:
    PhysicsBody(sf::Vector2<float> position, sf::Vector2<float> size, sf::Vector2<float> origin);
    virtual void translate(sf::Vector2<float> delta);
    virtual void rotate(float degrees);
    virtual void rotateWithCenter(float degrees, sf::Vector2<float> center);
    bool intersects(sf::Vector2<float> point);
    
//    debug utils
    void draw(sf::RenderWindow& window);
    
private:
    void updateCombinedTransform();
};
