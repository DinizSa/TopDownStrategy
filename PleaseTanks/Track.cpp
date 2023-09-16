//
//  Track.cpp
//  PleaseTanks
//
//  Created by Diniz Sá on 14/09/2023.
//

#include "Track.hpp"

Track::Track(sf::Vector2<float> size) : Drawable(size, "/Users/Shared/merda/PleaseTanks/images/Track_1_A.png") {
//    PhysicsBody::rect.setSize(size);
    Drawable::rect.setSize(size);
//    PhysicsBody::rect.setOrigin({size.x/2, size.y/2});
    Drawable::rect.setOrigin({size.x/2, size.y/2});
}

//void Track::translate(sf::Vector2<float> delta) {
////    PhysicsBody::translate(delta);
//    Drawable::translate(delta);
//}
void Track::rotate(float deltaAngle) {
//    PhysicsBody::rotate(deltaAngle);
    Drawable::rotate(deltaAngle);
}
void Track::rotateWithCenter(float degrees, sf::Vector2<float> center) {
//    PhysicsBody::rotateWithCenter(degrees, center);
    Drawable::rotateWithCenter(degrees, center);
}

void Track::draw(sf::RenderWindow& window) {
    Drawable::draw(window);
//    PhysicsBody::draw(window);
}
