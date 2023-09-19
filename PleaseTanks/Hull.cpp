//
//  Hull.cpp
//  PleaseTanks
//
//  Created by Diniz Sá on 14/09/2023.
//

#include "Hull.hpp"

Hull::Hull(sf::Vector2f size) : Body(size, {size.x*(6.f/10.f), size.y}, "/Users/Shared/merda/PleaseTanks/images/Hull_03.png") {
    setMovementCollisions(true);
}
