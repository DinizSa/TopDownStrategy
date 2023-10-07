//
//  CombatUnit.hpp
//  PleaseTanks
//
//  Created by Diniz Sá on 30/09/2023.
//

#pragma once

#include "Health.hpp"
#include "GunParams.hpp"

class CombatUnit: public PhysicsBody, public Health {
private:
    float startTurnDistance;
public:
    float maxDistancePerTurn;
    CombatUnit(sf::Vector2f size, float maxHealth, float armour, float maxDistance): PhysicsBody(size), Health(maxHealth, armour), maxDistancePerTurn(maxDistance) {
        PhysicsBody::traveledDistance.subscribe([&](float distance){
            if (canMove && maxDistancePerTurn  > 0.01f && distance > startTurnDistance + maxDistancePerTurn) {
                PhysicsBody::canMove = false;
                setVelocity({0.f, 0.f});
                PhysicsBody::path.clear(); 
                startTurnDistance = distance;
            }
        });
    };
    virtual ~CombatUnit(){};
    virtual bool attackPrimary() {return false;};
    virtual bool attackSecondary() {return false;};
    virtual std::shared_ptr<Weapon> getPrimaryWeapon() const = 0;
    virtual std::shared_ptr<Weapon> getSecondaryWeapon() const = 0;
    void resetTurn(){
        PhysicsBody::canMove = true;
    };
};
