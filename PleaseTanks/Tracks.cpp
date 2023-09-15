//
//  Tracks.cpp
//  PleaseTanks
//
//  Created by Diniz Sá on 14/09/2023.
//

#include "Tracks.hpp"

Tracks::Tracks(sf::Vector2<float> size): deltaCenter({(-2.f/10.f) * size.x, 0}), trackA({size.x/4, size.y}), trackB({size.x/4, size.y}) {
    trackA.translate(-deltaCenter);
    trackB.translate(deltaCenter);
}

void Tracks::draw(sf::RenderWindow& window) {
    trackA.draw(window);
    trackB.draw(window);
}

void Tracks::rotate(float degrees) {
    trackA.rotateWithCenter(degrees, deltaCenter);
    trackB.rotateWithCenter(degrees, -deltaCenter);
}
void Tracks::translate(sf::Vector2<float> delta) {
    trackA.translate(delta);
    trackB.translate(delta);
}
