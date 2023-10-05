//
//  Projectile.cpp
//  PleaseTanks
//
//  Created by Diniz Sá on 20/09/2023.
//

#import <algorithm>

#include "Explosion.hpp"
#include "Utils.hpp"
#include "AutoSprite.hpp"
#include "CombatUnit.hpp"

Explosion::Explosion(sf::Vector2f position, int maskId, const std::shared_ptr<Weapon> weapon):
PhysicsBody(weapon->explosionPhysicsSize), AutoSprite(weapon->explosionImageSize, 4.f, *weapon->explosionSprite),
    damage(weapon->damage), armourPenetration(weapon->penetration), rampUpOpacity(weapon->rampUpExplosiveOpacity)
{
    setMovementCollisions(false);
    setCollisionMaskId(maskId);
    translate(position, false);
    
    setPosition(position, 0.f);
    setPosition(&centerWorld, &rotation);
    
    if (weapon->rampUpExplosiveOpacity) {
        setOpacity(0);
    }
    
    if (damage > 0) {
        std::vector<PhysicsBody*> collided = getCollided();
        for (auto body : collided) {
            CombatUnit* combatUnit = dynamic_cast<CombatUnit*>(body);
            if (combatUnit != nullptr) {
                combatUnit->receiveDamage(damage, armourPenetration);
            }
        }
    }
}
Explosion::~Explosion() {
}
void Explosion::updateDrawable() {
    AutoSprite::updateDrawable();
    
    if (rampUpOpacity) {
        int newOpacity = std::min(255, framesCounter*2);
        std::cout << "newOpacity: " << newOpacity << std::endl;
        setOpacity(newOpacity);
    }
}
