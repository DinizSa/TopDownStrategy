//
//  Tracks.hpp
//  PleaseTanks
//
//  Created by Diniz Sá on 14/09/2023.
//

#pragma once
#include "Drawable.hpp"
#include "Track.hpp"

class Tracks {
public:
    Track trackA, trackB;
    Tracks(sf::Vector2<float> size);
    void draw(sf::RenderWindow& window);

//    put in interface to avoid unecessary specific cases
    void translate(sf::Vector2<float> delta);
    void translate(float delta);
    void rotate(float currentAngle, float degrees);
};
