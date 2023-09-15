//
//  Hull.hpp
//  PleaseTanks
//
//  Created by Diniz Sá on 14/09/2023.
//

#pragma once
#include "Drawable.hpp"
#include "PhysicsBody.hpp"

class Hull : public Drawable, public PhysicsBody {
public:
    Hull(sf::Vector2<float> size);
    void draw(sf::RenderWindow& window, const sf::Transform* transform) override;
};
