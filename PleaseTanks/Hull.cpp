//
//  Hull.cpp
//  PleaseTanks
//
//  Created by Diniz Sá on 14/09/2023.
//

#include "Hull.hpp"

Hull::Hull(sf::Vector2<float> size) : Drawable(size, "/Users/Shared/merda/PleaseTanks/images/Hull_03.png") {
}

//void Hull::translate(sf::Vector2<float> delta) {
//    PhysicsBody::translate(delta);
//    Drawable::translate(delta);
//}
void Hull::rotate(float deltaAngle) {
//    PhysicsBody::rotate(deltaAngle);
    Drawable::rotate(deltaAngle);
}
void Hull::rotateWithCenter(float degrees, sf::Vector2<float> center) {
//    PhysicsBody::rotateWithCenter(degrees, center);
    Drawable::rotateWithCenter(degrees, center);
}

void Hull::draw(sf::RenderWindow& window) {
    Drawable::draw(window);
//    PhysicsBody::draw(window);
}
