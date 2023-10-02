//
//  Projectile.hpp
//  PleaseTanks
//
//  Created by Diniz Sá on 20/09/2023.
//

#pragma once

#include <vector>

#include "PhysicsBody.hpp"
#include "AutoSprite.hpp"
#include "AudioPlayer.hpp"
#include "Weapon.hpp"

class Explosion : public PhysicsBody, public AutoSprite, protected AudioPlayer {
protected:
    float damage;
public:
    Explosion(sf::Vector2f position, int collisionMaskId, const std::shared_ptr<Weapon> weapon);
    ~Explosion();
};

//class FireExplosion : public Explosion {
//public:
//    FireExplosion(sf::Vector2f size, sf::Vector2f position, int collisionMaskId, float damage);
//};
//
//class LaunchExplosion : public Explosion {
//public:
//    LaunchExplosion(sf::Vector2f size, sf::Vector2f pozition);
//};
//
//class BulletExplosion : public Explosion {
//public:
//    BulletExplosion(sf::Vector2f size, sf::Vector2f pozition, int collisionMaskId, float damage);
//};
