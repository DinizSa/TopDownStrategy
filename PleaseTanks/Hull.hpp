//
//  Hull.hpp
//  PleaseTanks
//
//  Created by Diniz Sá on 14/09/2023.
//

#pragma once
#include "Drawable.hpp"
#include "PhysicsBody.hpp"

class Hull : public Drawable {
public:
    Hull(sf::Vector2<float> size);
    virtual void draw(sf::RenderWindow& window) override;
//    void translate(sf::Vector2<float> delta) override;
    void rotate(float degrees) override;
    void rotateWithCenter(float degrees, sf::Vector2<float> center) override;
};
