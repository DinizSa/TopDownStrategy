//
//  Configs.hpp
//  PleaseTanks
//
//  Created by Diniz Sá on 17/09/2023.
//

#pragma once
#include <SFML/Graphics.hpp>

struct CONFIGS {
    static constexpr float FPS = 60.f;
    static const int maxDistanceBySpeedFactor = 200;
    static sf::Vector2<int> windowSize;
    static sf::Color primaryColor;
    static sf::Color baseColor;
};
