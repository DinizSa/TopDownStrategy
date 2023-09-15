//
//  Tracks.hpp
//  PleaseTanks
//
//  Created by Diniz Sá on 14/09/2023.
//

#pragma once
#include "Drawable.hpp"
#include "PhysicsBody.hpp"
#include "Track.hpp"

class Tracks {
private:
    sf::Vector2<float> deltaCenter;
    
public:
    Track trackA, trackB;
    Tracks(sf::Vector2<float> size);
    void draw(sf::RenderWindow& window);

//    put in interface to avoid unecessary specific cases
    void translate(sf::Vector2<float> delta);
    void rotate(float degrees);
};
