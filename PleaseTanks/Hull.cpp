//
//  Hull.cpp
//  PleaseTanks
//
//  Created by Diniz Sá on 14/09/2023.
//

#include "Hull.hpp"

Hull::Hull(sf::Vector2f size, int spriteIndex) : Body(size, {size.x*(6.f/10.f), size.y}, SpriteNames::hulls, spriteIndex) {
    setMovementCollisions(true);
}
