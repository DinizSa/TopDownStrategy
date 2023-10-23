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
#include "VisionMask.hpp"
#include "UnitHud.hpp"

struct Drag {
    sf::Vector2f start;
    sf::Vector2f current;
    bool isDragging, isFinish;
    Drag(): isDragging(false), isFinish(false) {}
};

struct PressedButtons {
    bool moveFront, moveBack, rotateClock, rotateAntiClock, rotateSecondaryClock, rotateSecondaryAntiClock, attackPrimary, attackSecondary;
    Drag drag;
    PressedButtons(): moveFront(false), moveBack(false), rotateClock(false), rotateAntiClock(false), rotateSecondaryClock(false), rotateSecondaryAntiClock(false), attackPrimary(false), attackSecondary(false) {};
};

class Gameplay: public VisionMask {
public:
    enum PlayerTurn { playerA, playerB};
private:
    std::vector<CombatUnit*> teamA;
    std::vector<CombatUnit*> teamB;
    CombatUnit* selected;
    PlayerTurn playerTurn;
    bool paused;
    UnitHud unitHud;
public:
    Gameplay(): selected(nullptr), paused(false) {
        
        teamA.push_back(new Tank({80.f, 80.f}, {100.f, 200.f}, LightHullParams(), DoubleGunParams(), 4, 2.f, "Light Tank", Team::teamA));
        teamA.push_back(new Tank({90.f, 90.f}, {100.f, 400.f}, MediumHullParams(), SmokeGunParams(), 0, 1.5f, "Tank", Team::teamA));
        teamA.push_back(new Tank({100.f, 100.f}, {100.f, 600.f}, HeavyHullParams(), CannonPenetrationGunParams(), 2, 1.f, "Heavy Tank", Team::teamA));
        
        sf::Vector2f sizeSoldier = {50.f, 50.f};
        for (float y = 300.f; y < 500.f; y += 55.f) {
            teamA.push_back(new Soldier(sizeSoldier, {210.f, y}, Team::teamA));
        }
        
        teamB.push_back(new Tank({80.f, 80.f}, {1100.f, 200.f}, LightHullParams(), DoubleGunParams(), 4, 2.f, "Light Tank", Team::teamB));
        teamB.push_back(new Tank({90.f, 90.f}, {1100.f, 400.f}, MediumHullParams(), SmokeGunParams(), 0, 1.5f, "Tank", Team::teamB));
        teamB.push_back(new Tank({100.f, 100.f}, {1100.f, 600.f}, HeavyHullParams(), CannonPenetrationGunParams(), 2, 1.f, "Heavy Tank", Team::teamB));
        
        for (float y = 300.f; y < 500.f; y += 55.f) {
            teamB.push_back(new Soldier(sizeSoldier, {1000.f, y}, Team::teamB));
        }
        
        selected = teamA[0];
        
        playerTurn = PlayerTurn::playerA;
    }
    ~Gameplay() {
        for (auto combatUnit : teamA)
            delete combatUnit;
        for (auto combatUnit : teamB)
            delete combatUnit;
    }
    void update() {
        VisionMask::update(getCurrentTeam(), getNonCurrentTeam());
    }
    void handleClick(sf::Vector2f clickPoint) {
        if (paused)
            return;
        
        std::vector<CombatUnit*>& team = getCurrentTeam();
        for (auto combatUnit : team){
            if (combatUnit->instersects(clickPoint)){
                selected = combatUnit;
                unitHud.setSelectedUnit(selected);
                return;
            }
        }
        if (selected) {
            bool isUnitFromTeam = std::find(team.begin(), team.end(), selected) != team.end();
            if (isUnitFromTeam){
                selected->travelToDestination(clickPoint);
                return;
            }
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
    std::vector<CombatUnit*>& getNonCurrentTeam() {
        return playerTurn == PlayerTurn::playerA ? teamB : teamA;
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
    
    void draw(sf::RenderWindow& window) {
        VisionMask::draw(window);
        unitHud.draw(window);
    }
    
    void handleControls(PressedButtons buttons) {
        if (selected == nullptr)
            return;
        if (selected != nullptr) {
            if (buttons.drag.isDragging) {
                selected->handleDrag(buttons.drag.current - buttons.drag.start, false);
            } else if (buttons.drag.isFinish) {
                selected->handleDrag(buttons.drag.current - buttons.drag.start, true);
            }
        }
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
};
