//
//  Track.hpp
//  PleaseTanks
//
//  Created by Diniz Sá on 14/09/2023.
//

#pragma once
#include "Drawable.hpp"
#include "PhysicsBody.hpp"

class Track : public Drawable {
public:
    Track(sf::Vector2<float> size);
//    void translate(sf::Vector2<float> deltaPosition) override;
    void rotate(float degrees) override;
    void rotateWithCenter(float degrees, sf::Vector2<float> center) override;
    void draw(sf::RenderWindow& window) override;
};
