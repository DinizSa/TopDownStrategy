//
//  Track.hpp
//  PleaseTanks
//
//  Created by Diniz Sá on 14/09/2023.
//

#pragma once
#include "Drawable.hpp"

class Track : public Drawable {
public:
    Track(sf::Vector2<float> size, sf::Vector2<float> deltaCenter);
};
