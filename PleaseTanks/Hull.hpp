//
//  Hull.hpp
//  PleaseTanks
//
//  Created by Diniz Sá on 14/09/2023.
//

#pragma once
#include "Body.hpp"

class Hull : public Body {
public:
    Hull(sf::Vector2<float> size, sf::Vector2<float> position);
};
