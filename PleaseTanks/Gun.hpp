//
//  Hull.hpp
//  PleaseTanks
//
//  Created by Diniz Sá on 14/09/2023.
//

#pragma once

#include "Drawable.hpp"
#include "PhysicsBody.hpp"
#include "Health.hpp"
#include "AudioPlayer.hpp"

class Gun : public PhysicsBody, public Drawable, private Health, private AudioPlayer {
private:
    float angularSpeed;
    int rotationCounter;
    void rotateGun(float speed);
public:
    Gun(sf::Vector2f size, int spriteIndex);
    void shot();
    void rotateClock();
    void rotateAntiClock();
    void receiveDamage(int damage) override;
    void update() override;
};
