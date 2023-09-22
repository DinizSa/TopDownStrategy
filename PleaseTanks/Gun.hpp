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
#include "Explosion.hpp"

class Gun : public PhysicsBody, public Drawable {
private:
    float angularSpeed;
    std::vector<Projectile*> projectiles;
    std::vector<Explosion*> explosions;
public:
    Gun(sf::Vector2f size, int spriteIndex);
    ~Gun();
    void update() override;
    void shot();
    
    float getAngularSpeed();
};
