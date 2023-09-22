//
//  Tank.hpp
//  PleaseTanks
//
//  Created by Diniz Sá on 14/09/2023.
//

#pragma once

#include <SFML/Graphics.hpp>

#include "Hull.hpp"
#include "Gun.hpp"
#include "Track.hpp"

class Tank {
    sf::Vector2f position;
    sf::Vector2f size;
    float speed, angularSpeed;
    Hull hull;
    Gun gun;
    Track trackA, trackB;

public:
    Tank(sf::Vector2f size, sf::Vector2f position);
    void moveFront();
    void moveBack();
    void rotateClock();
    void rotateAntiClock();
    void rotateGunClock();
    void rotateGunAntiClock();
    
    bool contains(sf::Vector2f point) const;
    
    void update();
    void setVelocity(sf::Vector2f velocity);
    void shot();
private:
    void translate(float delta);
    void translate(sf::Vector2f delta);
    void rotate(float degrees);
};
