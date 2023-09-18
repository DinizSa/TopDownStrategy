//
//  Hull.hpp
//  PleaseTanks
//
//  Created by Diniz Sá on 14/09/2023.
//

#pragma once
#include "Drawable.hpp"
#include "PhysicsBody.hpp"

class Body : public Drawable, public PhysicsBody {
public:
    Body(sf::Vector2<float> size, sf::Vector2<float> position, const std::string&& texturePath);

    void setDeltaCenter(sf::Vector2<float> deltaCenter) override;

    void translate(float delta) override;
    void translate(sf::Vector2<float> delta) override;
    void rotate(float deltaAngle) override;
    void rotateAroundParent(float currentAngle, float degrees) override;
};
