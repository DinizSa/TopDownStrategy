//
//  Track.cpp
//  PleaseTanks
//
//  Created by Diniz Sá on 14/09/2023.
//

#include "Track.hpp"

Track::Track(sf::Vector2<float> size) : Drawable(size, "/Users/Shared/merda/PleaseTanks/images/Track_1_A.png"), PhysicsBody({0.f, 0.f}, 20.f) {
    rect.setSize(size);
    rect.setOrigin({size.x/2, size.y/2});
}

void Track::draw(sf::RenderWindow& window) {
    Drawable::draw(window, &transform);
//    PhysicsBody::draw(window);
}
