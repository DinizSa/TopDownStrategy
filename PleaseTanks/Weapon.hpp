//
//  CombatUnit.hpp
//  PleaseTanks
//
//  Created by Diniz Sá on 30/09/2023.
//

#pragma once
#include "Configs.hpp"
#include "Sound.hpp"
#include "Observer.hpp"

class Ammunition {
private:
    int stored, loaded, maxLoad;
    
public:
    Ammunition(int amount, int maxLoad): stored(amount), loaded(0), maxLoad(maxLoad) {
        reload();
    };
protected:
    bool reload() {
        if (stored == 0)
            return false;
        
        int amountMissing = maxLoad - loaded;
        int amountToReload = std::min(stored, amountMissing);
        stored -= amountToReload;
        loaded += amountToReload;
        return true;
    };
    bool consume() {
        if (loaded == 0)
            return false;
        
        loaded--;
        return true;
    };
    bool loadedAmmo() {
        return loaded;
    }
    bool storedAmmo() {
        return stored;
    }
public:
    void addAmmunition(int amount, bool loadBullet) {
        stored += amount;
        
        if (loadBullet) {
            reload();
        }
    }
};

class Weapon : public Ammunition {
private:
    float secondsSinceShot, secondsSinceEmpty;
    bool readyFromReload, readyFromShot;
public:
    int amountShots;
    float range, damage, penetration, zIndex, velocityScalar, rotation, reloadTimeSeconds, shotsIntervalSeconds;
    float selfDetonationSeconds, collisionDetonationSeconds;
    sf::Vector2f projectileImageSize, projectilePhysicsSize, explosionImageSize, explosionPhysicsSize;
    bool explodeOnMaxRange, loseForceOnMaxRange, automatic;
    Subject<int> triggerAutomatic;
    
    std::unique_ptr<Sprite> missileSprite, explosionSprite;
    std::unique_ptr<Sound> launchSound, explosionSound;
    
    Weapon(int maxLoad): Ammunition(0, maxLoad), range(0.f), damage(0.f), penetration(0.f), reloadTimeSeconds(0.f), secondsSinceShot(0.f), readyFromReload(true), readyFromShot(true), collisionDetonationSeconds(-1), selfDetonationSeconds(-1), rotation(0.f), shotsIntervalSeconds(0), automatic(false) {};
    bool fire() {
        if (readyFromShot && readyFromReload && Ammunition::consume()) {
            secondsSinceShot = 0.f;
            readyFromShot = shotsIntervalSeconds == 0;
            if (reloadTimeSeconds > 0 && loadedAmmo() == 0) {
                secondsSinceEmpty = 0.f;
                readyFromReload = false;
            }
            if (loadedAmmo() == 0) {
                reload();
            }
            return true;
        }
        return false;
    };
    bool isReloading() {
        return !readyFromReload && storedAmmo() > 0;
    }
    void updateReloadTimer() {
        
        secondsSinceEmpty += 1.f/CONFIGS::FPS;
        if (!readyFromReload && secondsSinceEmpty > reloadTimeSeconds) {
            readyFromReload = true;
        }
            
        if (shotsIntervalSeconds > 0) {
            secondsSinceShot += 1.f/CONFIGS::FPS;
            if (!readyFromShot && secondsSinceShot >= shotsIntervalSeconds) {
                readyFromShot = true;
                
                if (automatic) {
                    triggerAutomatic = loadedAmmo();
                    triggerAutomatic.notify();
                }
            }
        }
    };
};

class Rifle : public Weapon {
public:
    Rifle(): Weapon(3) {
        reloadTimeSeconds = 2.f;
        shotsIntervalSeconds = 1.f;
        range = 250.f;
        damage = 30.f;
        penetration = 5.f;
        velocityScalar = 5.f;
        collisionDetonationSeconds = 0.f;
        projectileImageSize = {50.f, 50.f};
        projectilePhysicsSize = {5.f, 5.f};
        explosionImageSize = {80.f, 80.f};
        explosionPhysicsSize = {5.f, 5.f};
        explodeOnMaxRange = false;
        loseForceOnMaxRange = true;
        zIndex = 2.f;
        
        missileSprite = std::make_unique<Sprite>(SpriteNames::effects2, 14, 14, 0, false);
        launchSound = std::make_unique<Sound>(SoundNames::rifle, 50.f, false);
        
        explosionSprite = std::make_unique<Sprite>(SpriteNames::effects2, 17, 19, 80, false, true);
        explosionSound = std::make_unique<Sound>(SoundNames::bulletHitMetal, 100.f, false);
    };
};

class Grenade : public Weapon {
public:
    Grenade(): Weapon(1) {
        range = 150.f;
        damage = 60.f;
        penetration = 20.f;
        rotation = 0.4f;
        reloadTimeSeconds = 3.f;
        velocityScalar = 3.f;
        selfDetonationSeconds = 4.f;
        zIndex = 1.f;
        projectileImageSize = {20.f, 20.f};
        projectilePhysicsSize = {5.f, 5.f};
        explosionImageSize = {130.f, 130.f};
        explosionPhysicsSize = {100.f, 100.f};
        explodeOnMaxRange = false;
        loseForceOnMaxRange = false;
        
        missileSprite = std::make_unique<Sprite>(SpriteNames::grenade, 0, 0, 0, false);
        launchSound = std::make_unique<Sound>(SoundNames::grenadeThrow, 50.f, false);
        
        explosionSprite = std::make_unique<Sprite>(SpriteNames::effects, 21, 28, 80, false, true);
        explosionSound = std::make_unique<Sound>(SoundNames::grenadeExplosion, 50.f, false);
    };
};

class CannonHighExplosive : public Weapon {
public:
    CannonHighExplosive(): Weapon(1) {
        range = 550.f;
        damage = 120.f;
        penetration = 20.f;
        rotation = 0.f;
        reloadTimeSeconds = 4.f;
        velocityScalar = 7.f;
        zIndex = 2.f;
        collisionDetonationSeconds = 0.f;
        projectileImageSize = {65.f, 65.f};
        projectilePhysicsSize = {10.f, 10.f};
        explosionImageSize = {200.f, 200.f};
        explosionPhysicsSize = {150.f, 150.f};
        explodeOnMaxRange = true;
        loseForceOnMaxRange = false;
        
        missileSprite = std::make_unique<Sprite>(SpriteNames::effects2, 14, 14, 0, false);
        launchSound = std::make_unique<Sound>(SoundNames::tankGunBlast, 50.f, false);
        
        explosionSprite = std::make_unique<Sprite>(SpriteNames::effects, 21, 28, 80, false, true);
        explosionSound = std::make_unique<Sound>(SoundNames::bigExplosion, 100.f, false);
    };
};

class MineAntiTank : public Weapon {
public:
    MineAntiTank(): Weapon(1) {
        range = 0.f;
        damage = 200.f;
        penetration = 60.f;
        rotation = 0.f;
        reloadTimeSeconds = 0.f;
        velocityScalar = 0.f;
        zIndex = 1.f;
        collisionDetonationSeconds = 0.f;
        projectileImageSize = {45.f, 45.f};
        projectilePhysicsSize = {40.f, 40.f};
        explosionImageSize = {200.f, 200.f};
        explosionPhysicsSize = {150.f, 150.f};
        explodeOnMaxRange = true;
        loseForceOnMaxRange = false;
        
        missileSprite = std::make_unique<Sprite>(SpriteNames::mine, 0, 0, 0, false);
        
        explosionSprite = std::make_unique<Sprite>(SpriteNames::effects, 21, 28, 80, false, true);
        explosionSound = std::make_unique<Sound>(SoundNames::shellExplosion, 100.f, false);
        
        addAmmunition(1, true);
    };
};

class AutomaticRifle : public Weapon {
public:
    AutomaticRifle(): Weapon(5) {
        range = 200.f;
        damage = 20.f;
        penetration = 4.f;
        reloadTimeSeconds = 2.0f;
        shotsIntervalSeconds = 0.3;
        velocityScalar = 6.f;
        collisionDetonationSeconds = 0.f;
        projectileImageSize = {50.f, 50.f};
        projectilePhysicsSize = {5.f, 5.f};
        explosionImageSize = {50.f, 50.f};
        explosionPhysicsSize = {5.f, 5.f};
        explodeOnMaxRange = false;
        loseForceOnMaxRange = true;
        zIndex = 2.f;
        automatic = true;
        
        missileSprite = std::make_unique<Sprite>(SpriteNames::effects2, 14, 14, 0, false);
        launchSound = std::make_unique<Sound>(SoundNames::rifle, 50.f, false);
        
        explosionSprite = std::make_unique<Sprite>(SpriteNames::effects2, 17, 19, 80, false, true);
        explosionSound = std::make_unique<Sound>(SoundNames::bulletHitMetal, 100.f, false);
    };
};
