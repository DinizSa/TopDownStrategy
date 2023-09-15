//
//  Tank.hpp
//  PleaseTanks
//
//  Created by Diniz Sá on 14/09/2023.
//

#pragma once
#include "Hull.hpp"
#include "Gun.hpp"
#include "Tracks.hpp"
#include <SFML/Graphics.hpp>

class Tank {
    sf::Vector2<float> position;
    sf::Vector2<float> size;
    float speed, angularSpeed, gunAngularSpeed;
    Hull hull;
    Tracks tracks;
    Gun gun;

public:
    Tank(sf::Vector2<float> position);
    ~Tank();
    void moveFront();
    void moveBack();
    void rotateClock();
    void rotateAntiClock();
    void rotateGunClock();
    void rotateGunAntiClock();
    void draw(sf::RenderWindow& window);
private:
    void rotateGun(float degrees);
    void translate(sf::Vector2<float> delta);
    void rotate(float degrees);
};
