//
//  Hull.hpp
//  PleaseTanks
//
//  Created by Diniz Sá on 14/09/2023.
//

#pragma once
#include "AutoSprite.hpp"
#include "PhysicsBody.hpp"

class Hull : public PhysicsBody, public Drawable {
private:
    AutoSprite* exhaust;
    Subject<sf::Vector2f> exhaustPosition;
public:
    Hull(sf::Vector2f size, int spriteIndex);
    ~Hull();
};
