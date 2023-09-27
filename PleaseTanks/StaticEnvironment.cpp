//
//  StaticEnvironment.cpp
//  PleaseTanks
//
//  Created by Diniz Sá on 27/09/2023.
//

#include "StaticEnvironment.hpp"
#include "Drawable.hpp"

Tree::Tree(sf::Vector2f size, sf::Vector2f position): PhysicsBody(size/3.f) {
    translate(position, false);
    Drawable* tree = new Drawable(size, 4.f, SpriteNames::tree, 0);
    tree->setPosition(position, 0.f);
    setMovementCollisions(true);
}

Tree::~Tree() {}
