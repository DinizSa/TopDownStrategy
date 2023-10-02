//
//  Projectile.cpp
//  PleaseTanks
//
//  Created by Diniz Sá on 20/09/2023.
//

#include "Explosion.hpp"
#include "Utils.hpp"
#include "AutoSprite.hpp"
#include "CombatUnit.hpp"

Explosion::Explosion(sf::Vector2f position, int maskId, const std::shared_ptr<Weapon> weapon):
PhysicsBody(weapon->explosionPhysicsSize), AutoSprite(weapon->explosionImageSize, 4.f, *weapon->explosionSprite),
    damage(weapon->damage)
{
    setMovementCollisions(false);
    setCollisionMaskId(maskId);
    translate(position, false);
    
    setPosition(position, 0.f);
    setPosition(&centerWorld, &rotation);
    
    if (damage > 0) {
        std::vector<PhysicsBody*> collided = getCollided();
        for (auto body : collided) {
            CombatUnit* combatUnit = dynamic_cast<CombatUnit*>(body);
            if (combatUnit != nullptr) {
                combatUnit->receiveDamage(damage);
            }
        }
    }
}
Explosion::~Explosion() {
}
