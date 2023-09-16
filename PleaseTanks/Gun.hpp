//
//  Hull.hpp
//  PleaseTanks
//
//  Created by Diniz Sá on 14/09/2023.
//

#pragma once
#include "Drawable.hpp"
#include "PhysicsBody.hpp"

class Gun : public Drawable {
private:
//    float gunAngularSpeed;
public:
    Gun(sf::Vector2<float> size);
    void rotate(float degrees) override;
    void draw(sf::RenderWindow& window) override;
};
