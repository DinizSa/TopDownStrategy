//
//  CombatUnit.hpp
//  PleaseTanks
//
//  Created by Diniz Sá on 30/09/2023.
//

#pragma once

class Ammunition {
private:
    int stored;
    int loaded;
    
public:
    Ammunition(int amount): stored(amount), loaded(0) {
        reload();
    };
    void addAmmunition(int amount) {
        stored += amount;
    }
protected:
    bool reload() {
        if (stored == 0)
            return false;
        
        stored--;
        loaded++;
        return true;
    };
    bool consume() {
        if (loaded == 0)
            return false;

        loaded--;
        return true;
    };
};
class Weapon : public Ammunition {
public:
    float range, damage, penetration, reloadTimeSeconds, secondsSinceShot;
    bool recharged;
    
    Weapon(float range, float damage, float penetration, float reloadTimeSeconds, int ammunitionAmount): Ammunition(ammunitionAmount), range(range), damage(damage), penetration(penetration), reloadTimeSeconds(reloadTimeSeconds), secondsSinceShot(0.f), recharged(true) {
        reload();
    };
    bool fire() {
        if (recharged && consume()) {
            secondsSinceShot = 0.f;
            recharged = false;
            return true;
        }
        return false;
    };
    void updateReloadTimer() {
        secondsSinceShot += 1.f/60;
        if (!recharged && secondsSinceShot >= reloadTimeSeconds) {
            reload();
            recharged = true;
        }
    };
};

class CombatUnit {
public:
    virtual void receiveDamage(int damage) {};
    virtual bool attack() {return false;};
};
