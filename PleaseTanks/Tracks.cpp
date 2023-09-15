//
//  Tracks.cpp
//  PleaseTanks
//
//  Created by Diniz Sá on 14/09/2023.
//

#include "Tracks.hpp"

Tracks::Tracks(sf::Vector2<float> size): deltaCenter({(-2.f/10.f) * size.x, 0}), trackA({size.x/4, size.y}), trackB({size.x/4, size.y}) {
    trackA.translateWorld(-deltaCenter);
    trackB.translateWorld(deltaCenter);
}

void Tracks::draw(sf::RenderWindow& window) {
    trackA.draw(window);
    trackB.draw(window);
}

void Tracks::rotate(float degrees) {
    trackA.rotateWithCenterWorld(degrees, deltaCenter);
    trackB.rotateWithCenterWorld(degrees, -deltaCenter);
}
void Tracks::translate(sf::Vector2<float> delta) {
    trackA.translateWorld(delta);
    trackB.translateWorld(delta);
}
