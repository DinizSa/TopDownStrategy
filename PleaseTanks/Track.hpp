//
//  Track.hpp
//  PleaseTanks
//
//  Created by Diniz Sá on 14/09/2023.
//

#pragma once
#include "Drawable.hpp"
#include "PhysicsBody.hpp"

class Track : public Drawable, public PhysicsBody {
public:
    Track(sf::Vector2<float> size);
    void draw(sf::RenderWindow& window) override;
};
