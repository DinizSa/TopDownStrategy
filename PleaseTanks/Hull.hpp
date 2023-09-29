//
//  Hull.hpp
//  PleaseTanks
//
//  Created by Diniz Sá on 14/09/2023.
//

#pragma once
#include "AutoSprite.hpp"
#include "PhysicsBody.hpp"
#include "Health.hpp"
#include "AudioPlayer.hpp"

class Hull : public PhysicsBody, public Drawable, private Health, private AudioPlayer {
private:
    AutoSprite* exhaust;
    Subject<sf::Vector2f> exhaustPosition;
    int movingCounter;
    float speed;
public:
    Hull(sf::Vector2f size, int spriteIndex);
    ~Hull();
    void receiveDamage(int damage) override;
    void update() override;
    void setSpeed(float newSpeed);
    float getSpeed() const;
};
