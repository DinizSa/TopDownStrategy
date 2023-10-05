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
#include "Health.hpp"
#include "HullParams.hpp"

class Hull : public PhysicsBody, public Drawable, public Health, private AudioPlayer {
private:
    AutoSprite* exhaust;
    Subject<sf::Vector2f> exhaustPosition;
    AutoSprite* damageSmoke;
    std::unique_ptr<Sound> workingSound;
public:
    Hull(HullParams&& params);
    ~Hull();
    float receiveDamage(float damage, float armourPenetration) override;
    float getSpeed() const;
};
