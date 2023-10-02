//
//  CombatUnit.hpp
//  PleaseTanks
//
//  Created by Diniz Sá on 30/09/2023.
//

#pragma once
#include "Configs.hpp"
#include "Sound.hpp"

class Ammunition {
private:
    int stored;
    int loaded;
    
public:
    Ammunition(int amount): stored(amount), loaded(0) {
        reload();
    };
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
    float secondsSinceShot;
    bool recharged;
public:
    float range, damage, penetration, reloadTimeSeconds, zIndex, velocityScalar, rotation;
    float selfDetonationSeconds, collisionDetonationSeconds;
    sf::Vector2f projectileImageSize, projectilePhysicsSize, explosionImageSize, explosionPhysicsSize;
    bool explodeOnMaxRange, loseForceOnMaxRange;
    
    std::unique_ptr<Sprite> missileSprite, explosionSprite;
    std::unique_ptr<Sound> launchSound, explosionSound;
    
    Weapon(): Ammunition(0), range(0.f), damage(0.f), penetration(0.f), reloadTimeSeconds(0.f), secondsSinceShot(0.f), recharged(true), collisionDetonationSeconds(-1), selfDetonationSeconds(-1), rotation(0.f) {};
    bool fire() {
        if (recharged && consume()) {
            secondsSinceShot = 0.f;
            recharged = false;
            return true;
        }
        return false;
    };
    void updateReloadTimer() {
        secondsSinceShot += 1.f/CONFIGS::FPS;
        if (!recharged && secondsSinceShot >= reloadTimeSeconds) {
            reload();
            recharged = true;
        }
    };
};

class Rifle : public Weapon {
public:
    Rifle() {
        range = 250.f;
        damage = 30.f;
        penetration = 5.f;
        reloadTimeSeconds = 2.f;
        velocityScalar = 5.f;
        collisionDetonationSeconds = 0.f;
        projectileImageSize = {60.f, 60.f};
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
    Grenade() {
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
    CannonHighExplosive() {
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
    MineAntiTank() {
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
    };
};
