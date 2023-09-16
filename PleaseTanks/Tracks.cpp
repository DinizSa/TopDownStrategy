//
//  Tracks.cpp
//  PleaseTanks
//
//  Created by Diniz Sá on 14/09/2023.
//

#include "Tracks.hpp"

Tracks::Tracks(sf::Vector2<float> size): trackA({size.x/4, size.y}, {(2.f/10.f) * size.x, 0}), trackB({size.x/4, size.y}, {(-2.f/10.f) * size.x, 0}) {
}

void Tracks::rotate(float currentAngle, float degrees) {
    trackA.rotateAroundParent(currentAngle, degrees);
    trackB.rotateAroundParent(currentAngle, degrees);
}
void Tracks::translate(sf::Vector2<float> delta) {
    trackA.translate(delta);
    trackB.translate(delta);
}
void Tracks::translate(float delta) {
    trackA.translate(delta);
    trackB.translate(delta);
}

void Tracks::draw(sf::RenderWindow& window) {
    trackA.draw(window);
    trackB.draw(window);
}
