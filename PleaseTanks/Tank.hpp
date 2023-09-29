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
private:
    sf::Vector2f position;
    sf::Vector2f size;
    float angularSpeed;
    Gun gun;
    Track trackA, trackB;
    Hull hull;
    
private:
    void translate(float delta);
    void translate(sf::Vector2f delta);
    void rotate(float degrees);

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
    void travelToDestination(sf::Vector2f& destination);
};
