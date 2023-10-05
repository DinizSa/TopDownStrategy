//
//  Hull.hpp
//  PleaseTanks
//
//  Created by Diniz Sá on 14/09/2023.
//

#pragma once
#include "AutoSprite.hpp"
#include "PhysicsBody.hpp"
#include "Health.hpp"
#include "AudioPlayer.hpp"
#include "CombatUnit.hpp"
#include "HullParams.hpp"

class Hull : public PhysicsBody, public Drawable, public CombatUnit, private AudioPlayer {
private:
    AutoSprite* exhaust;
    Subject<sf::Vector2f> exhaustPosition;
    AutoSprite* damageSmoke;
    std::unique_ptr<Sound> workingSound;
    std::unique_ptr<Sound> sufferDamageSound;
public:
    Hull(HullParams&& params);
    ~Hull();
    void receiveDamage(float damage, float armourPenetration) override;
    float getSpeed() const;
};
