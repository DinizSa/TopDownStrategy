//
//  Hull.hpp
//  PleaseTanks
//
//  Created by Diniz Sá on 14/09/2023.
//

#pragma once
#include "Drawable.hpp"
#include "PhysicsBody.hpp"

class Gun : public Drawable, public PhysicsBody {
private:
//    float gunAngularSpeed;
public:
    Gun(sf::Vector2<float> size);
    virtual void draw(sf::RenderWindow& window);
};
