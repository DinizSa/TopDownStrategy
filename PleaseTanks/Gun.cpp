//
//  Hull.cpp
//  PleaseTanks
//
//  Created by Diniz Sá on 14/09/2023.
//

#include "Gun.hpp"

Gun::Gun(sf::Vector2<float> size) : Drawable(size, "/Users/Shared/merda/PleaseTanks/images/Gun_01.png") {
}

//void Gun::translate(sf::Vector2<float> delta) {
////    PhysicsBody::translate(delta);
//    Drawable::translate(delta);
//}
void Gun::rotate(float deltaAngle) {
//    PhysicsBody::rotate(deltaAngle);
    Drawable::rotate(deltaAngle);
}
void Gun::rotateWithCenter(float degrees, sf::Vector2<float> center) {
//    PhysicsBody::rotateWithCenter(degrees, center);
    Drawable::rotateWithCenter(degrees, center);
}

void Gun::draw(sf::RenderWindow& window) {
    Drawable::draw(window);
//    PhysicsBody::draw(window);
}
