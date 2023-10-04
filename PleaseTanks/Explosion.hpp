//
//  Projectile.hpp
//  PleaseTanks
//
//  Created by Diniz Sá on 20/09/2023.
//

#pragma once

#include <vector>

#include "PhysicsBody.hpp"
#include "AutoSprite.hpp"
#include "AudioPlayer.hpp"
#include "Weapon.hpp"

class Explosion : public PhysicsBody, public AutoSprite, protected AudioPlayer {
protected:
    float damage;
    bool rampUpOpacity;
public:
    Explosion(sf::Vector2f position, int collisionMaskId, const std::shared_ptr<Weapon> weapon);
    ~Explosion();
    virtual void updateDrawable() override;
};
