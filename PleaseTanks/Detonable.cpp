//
//  Detonable.cpp
//  PleaseTanks
//
//  Created by Diniz Sá on 20/09/2023.
//

#include "Detonable.hpp"
#include "Utils.hpp"
#include "AutoSprite.hpp"

std::vector<Detonable*> Detonable::detonables;

void Detonable::addDetonable(Detonable* detonable) {
    Detonable::detonables.push_back(detonable);
}
void Detonable::removeDetonable(Detonable* detonable) {
    Detonable::detonables.erase(std::remove(Detonable::detonables.begin(), Detonable::detonables.end(), detonable), Detonable::detonables.end());
}
void Detonable::updateDetonables() {
    for (auto detonable : detonables) {
        detonable->updateDetonable();
    }
    
    for (auto it = Detonable::detonables.begin(); it != Detonable::detonables.end();) {
        Detonable* detonable = *it;
        if (detonable->isDestroyed()) {
            delete detonable;
        } else {
            it++;
        }
    }
}

Detonable::Detonable(sf::Vector2f size, sf::Vector2f physicsBodySize, sf::Vector2f position, float angleDegrees, int maskId, Sprite sprite, float velocityScalar):
    PhysicsBody(physicsBodySize),
    AutoSprite(size, PhysicsBody::centerWorld, PhysicsBody::rotation, 4.f, sprite),
    velocityScalar(velocityScalar), destroyed(false)
{
    setCollisionMaskId(maskId);
    translate(position, false);

    setMovementCollisions(true);
}
Detonable::~Detonable() {}
bool Detonable::isDestroyed() {
    return destroyed;
}


FireProjectile::FireProjectile(sf::Vector2f position, float angleDegrees, int collisionMaskId):
    Detonable({150.f, 150.f}, {20.f, 20.f}, position, angleDegrees, collisionMaskId, {SpriteNames::effects, 10, 19, 80, true}, 10.f)
{
    sf::Vector2f velocity = Utils::getVector(angleDegrees, velocityScalar);
    setVelocityAndRotate(velocity);
    
    Detonable::addDetonable(this);
}
FireProjectile::~FireProjectile() {
    Detonable::removeDetonable(this);
}
void FireProjectile::updateDetonable() {
    if (getTraveledDistance() > 1000.f) {
        destroyed = true;
        return;
    }
    
    bool collided = !applyVelocity();
    if (collided) {
        new FireExplosion(centerWorld(), collisionMaskId);
        destroyed = true;
    }
}


FireExplosion::FireExplosion(sf::Vector2f position, int collisionMaskId):
    Detonable({200.f, 200.f}, {50.f, 50.f}, position, 0.f, collisionMaskId, {SpriteNames::effects, 21, 28, 80, false}, 0.f)
{
    auto collided = getCollided();
    std::cout << "collided: " << collided.size() << '\n';
}
