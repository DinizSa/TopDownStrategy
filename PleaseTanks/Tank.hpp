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
#include "CombatUnit.hpp"
#include "AudioPlayer.hpp"
#include "HullParams.hpp"
#include "GunParams.hpp"

class Tank : public CombatUnit, private AudioPlayer {
private:
    float angularSpeed;
    Gun gun;
    Track trackA, trackB;
    Hull hull;

public:
    Tank(sf::Vector2f size, sf::Vector2f position, HullParams hullParams, GunParams gunParams, int trackId, float angularSpeed, std::string category);
    void rotateSecondaryClock() override;
    void rotateSecondaryAntiClock() override;
    
    bool translate(float delta, bool isTravel = true) override;
    bool translate(sf::Vector2f delta, bool isTravel = true) override;
    bool rotate(float degrees) override;
    
    bool attackPrimary() override;
    bool attackSecondary() override;
    bool canMove();
    bool canAttack();
    
    std::shared_ptr<Weapon> getPrimaryWeapon() const override;
    std::shared_ptr<Weapon> getSecondaryWeapon() const override;
};
