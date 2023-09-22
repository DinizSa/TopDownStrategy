//
//  Hull.hpp
//  PleaseTanks
//
//  Created by Diniz Sá on 14/09/2023.
//

#pragma once
#include "Drawable.hpp"
#include "PhysicsBody.hpp"
#include "Projectile.hpp"

class Gun : public PhysicsBody, public Drawable {
private:
    float angularSpeed;
    std::vector<Projectile*> projectiles;
public:
    Gun(sf::Vector2f size, int spriteIndex);
    ~Gun();
    void update() override;
    void shot();
    
    float getAngularSpeed();
    virtual void draw(sf::RenderWindow& window) override;
};
