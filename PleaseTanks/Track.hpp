//
//  Track.hpp
//  PleaseTanks
//
//  Created by Diniz Sá on 14/09/2023.
//

#pragma once
#include "Drawable.hpp"
#include "PhysicsBody.hpp"

class Track : public PhysicsBody, public Drawable {
private:
    float distanceToChangeSprite;
public:
    Track(sf::Vector2f size, int spriteIndex);
    
    bool translate(sf::Vector2f delta) override;
};
