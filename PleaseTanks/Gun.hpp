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
#include "CombatUnit.hpp"
#include "Weapon.hpp"
#include "AutoSprite.hpp"
#include "GunParams.hpp"

class Gun : public CombatUnit, public Drawable, private AudioPlayer {
private:
    GunParams gunParams;
    
    void setupGun(int initialAmmunition);
public:
    Gun(GunParams&& GunParams);
    virtual ~Gun();
    bool attackPrimary() override;
    bool attackSecondary() override;
    void update() override;
};
