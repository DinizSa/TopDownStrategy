//
//  Track.hpp
//  PleaseTanks
//
//  Created by Diniz Sá on 14/09/2023.
//

#pragma once

#include "PhysicsBody.hpp"
#include "AutoSprite.hpp"

class TrackTrail : public AutoSprite {
private:
    float currentOpacity;
    float deltaOpacity;

protected:
    void updateDrawable() override;
    
public:
    TrackTrail(sf::Vector2f size, int spriteIndex, sf::Vector2f position, float rotation);
    ~TrackTrail();
};
