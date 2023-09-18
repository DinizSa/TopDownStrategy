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
    sf::Vector2<float> position;
    sf::Vector2<float> size;
    float speed, angularSpeed;
    Hull hull;
    Gun gun;
    Track trackA, trackB;

public:
    Tank(sf::Vector2<float> size, sf::Vector2<float> position);
    ~Tank();
    void moveFront();
    void moveBack();
    void rotateClock();
    void rotateAntiClock();
    void rotateGunClock();
    void rotateGunAntiClock();
    void draw(sf::RenderWindow& window);
private:
    void translate(float delta);
    void translate(sf::Vector2<float> delta);
    void rotate(float degrees);
};
