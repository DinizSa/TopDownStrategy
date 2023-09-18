//
//  Hull.hpp
//  PleaseTanks
//
//  Created by Diniz Sá on 14/09/2023.
//

#pragma once
#include "Body.hpp"

class Gun : public Body {
private:
    float angularSpeed;
public:
    Gun(sf::Vector2<float> size, sf::Vector2<float> position);
    
    float getAngularSpeed();
    void rotate(float deltaAngle) override;
    void rotateAroundParent(float currentAngle, float degrees) override;
};
