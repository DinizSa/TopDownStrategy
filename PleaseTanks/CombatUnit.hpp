//
//  CombatUnit.hpp
//  PleaseTanks
//
//  Created by Diniz Sá on 30/09/2023.
//

#pragma once

#include "Health.hpp"
#include "GunParams.hpp"
enum Team { teamA, teamB};
class CombatUnit: public PhysicsBody, public Health {
private:
    float startTurnDistance;
public:
    std::string category;
    Team team;
    float depthOfVision;
    float maxDistancePerTurn;
    CombatUnit(sf::Vector2f size, float maxHealth, float armour, float maxDistance, std::string category, Team team, float depthOfVision): PhysicsBody(size), Health(maxHealth, armour), maxDistancePerTurn(maxDistance), category(category), team(team), depthOfVision(depthOfVision) {
        PhysicsBody::traveledDistance.subscribe([&](float distance){
            if (canMove && maxDistancePerTurn  > 0.01f && distance > startTurnDistance + maxDistancePerTurn) {
                PhysicsBody::canMove = false;
                startTurnDistance = distance;
                cancelPath();
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
        setVisible(true);
        startTurnDistance = PhysicsBody::traveledDistance();
        cancelPath();
    };
    virtual void setVisible(bool visible) = 0;
    virtual bool isVisible() = 0;
    virtual void handleDrag(sf::Vector2f deltaDrag, bool isFinished) {};
};
