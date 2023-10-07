//
//  Gameplay.hpp
//  PleaseTanks
//
//  Created by Diniz Sá on 05/10/2023.
//

#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Tank.hpp"
#include "Soldier.hpp"

struct PressedButtons {
    bool moveFront, moveBack, rotateClock, rotateAntiClock, rotateSecondaryClock, rotateSecondaryAntiClock, attackPrimary, attackSecondary;
};

class Gameplay {
public:
    enum PlayerTurn { playerA, playerB};
private:
    std::vector<CombatUnit*> teamA;
    std::vector<CombatUnit*> teamB;
    CombatUnit* selected;
    PlayerTurn playerTurn;
    bool paused;
public:
    Gameplay(): selected(nullptr) {
        
        teamA.push_back(new Tank({80.f, 80.f}, {100.f, 200.f}, LightHullParams(), DoubleGunParams(), 4, 2.f, "Light Tank"));
        teamA.push_back(new Tank({90.f, 90.f}, {100.f, 400.f}, MediumHullParams(), SmokeGunParams(), 0, 1.5f, "Tank"));
        teamA.push_back(new Tank({100.f, 100.f}, {100.f, 600.f}, HeavyHullParams(), CannonPenetrationGunParams(), 2, 1.f, "Heavy Tank"));
        
        sf::Vector2f sizeSoldier = {50.f, 50.f};
        for (float y = 300.f; y < 500.f; y += 55.f) {
            teamA.push_back(new Soldier(sizeSoldier, {210.f, y}));
        }
        
        teamB.push_back(new Tank({80.f, 80.f}, {1100.f, 200.f}, LightHullParams(), DoubleGunParams(), 4, 2.f, "Light Tank"));
        teamB.push_back(new Tank({90.f, 90.f}, {1100.f, 400.f}, MediumHullParams(), SmokeGunParams(), 0, 1.5f, "Tank"));
        teamB.push_back(new Tank({100.f, 100.f}, {1100.f, 600.f}, HeavyHullParams(), CannonPenetrationGunParams(), 2, 1.f, "Heavy Tank"));
        
        for (float y = 300.f; y < 500.f; y += 55.f) {
            teamB.push_back(new Soldier(sizeSoldier, {1000.f, y}));
        }
        
        playerTurn = PlayerTurn::playerA;
    }
    void handleClick(sf::Vector2f clickPoint) {
        if (paused)
            return;
        
        std::vector<CombatUnit*>& team = getCurrentTeam();
        for (auto combatUnit : team){
            if (combatUnit->instersects(clickPoint)){
                selected = combatUnit;
                return;
            }
        }
        if (selected) {
            bool isUnitFromTeam = std::find(team.begin(), team.end(), selected) != team.end();
            if (isUnitFromTeam)
                selected->travelToDestination(clickPoint);
        }
    }
    CombatUnit* getSelected() {
        return selected;
    }
    void togglePause() {
        paused = !paused;
    }
    
    std::vector<CombatUnit*>& getCurrentTeam() {
        return playerTurn == PlayerTurn::playerA ? teamA : teamB;
    }
    
    void togglePlayTurn() {
        
        playerTurn = playerTurn == PlayerTurn::playerB ? PlayerTurn::playerA : PlayerTurn::playerB;
        
        std::vector<CombatUnit*>& team = getCurrentTeam();
        for (auto combatUnit : team) {
            combatUnit->resetTurn();
        }
        selected = nullptr;
    }
    bool isPaused() {
        return paused;
    }
    PlayerTurn getPlayerTurn() {
        return playerTurn;
    }
    
    void handleControls(PressedButtons buttons) {
        if (selected == nullptr)
            return;
        if (buttons.moveFront)
            selected->translateFront();
        if (buttons.moveBack)
            selected->translateBack();
        if (buttons.rotateClock)
            selected->rotateClock();
        if (buttons.rotateAntiClock)
            selected->rotateAntiClock();
        if (buttons.rotateSecondaryClock)
            selected->rotateSecondaryClock();
        if (buttons.rotateSecondaryAntiClock)
            selected->rotateSecondaryAntiClock();
        if (buttons.attackPrimary)
            selected->attackPrimary();
        if (buttons.attackSecondary)
            selected->attackSecondary();
    }
    
    ~Gameplay() {
        for (auto combatUnit : teamA)
            delete combatUnit;
        for (auto combatUnit : teamB)
            delete combatUnit;
    }
};
