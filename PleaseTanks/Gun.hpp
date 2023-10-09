//
//  Hull.hpp
//  PleaseTanks
//
//  Created by Diniz Sá on 14/09/2023.
//

#pragma once

#include "PhysicsBody.hpp"
#include "Health.hpp"
#include "AudioPlayer.hpp"
#include "AudioPlayer.hpp"
#include "Weapon.hpp"
#include "AutoSprite.hpp"
#include "GunParams.hpp"

class Gun : public PhysicsBody, public Health, public Drawable, private AudioPlayer {
public:
    Gun(GunParams&& GunParams);
    virtual ~Gun();
    bool attackPrimary(float forcePercentage = 100.f);
    bool attackSecondary(float forcePercentage = 100.f);
    void update() override;
    std::shared_ptr<Weapon> getPrimary() const;
    std::shared_ptr<Weapon> getSecondary() const;
    
    void handleDrag(sf::Vector2f deltaDrag, bool isFinished);
    
private:
    GunParams gunParams;
    
    void setupGun(int initialAmmunition);
};
