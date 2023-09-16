//
//  Track.cpp
//  PleaseTanks
//
//  Created by Diniz Sá on 14/09/2023.
//

#include "Track.hpp"

Track::Track(sf::Vector2<float> size) : Drawable(size, "/Users/Shared/merda/PleaseTanks/images/Track_1_A.png") {
    Drawable::rect.setSize(size);
    Drawable::rect.setOrigin({size.x/2, size.y/2});
}

void Track::rotate(float deltaAngle) {
    Drawable::rotate(deltaAngle);
}
void Track::rotateWithCenter(float degrees, sf::Vector2<float> center) {
    Drawable::rotateWithCenter(degrees, center);
}

void Track::draw(sf::RenderWindow& window) {
    Drawable::draw(window);
}
