//
//  Track.hpp
//  PleaseTanks
//
//  Created by Diniz Sá on 14/09/2023.
//

#pragma once
#include "Body.hpp"

class Track : public Body {
private:
    int index;
    float traveledDistance;
public:
    Track(sf::Vector2f size, int spriteIndex);
    
    bool translate(sf::Vector2f delta) override;
};
