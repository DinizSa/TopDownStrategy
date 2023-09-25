//
//  Track.cpp
//  PleaseTanks
//
//  Created by Diniz Sá on 14/09/2023.
//

#include "TrackTrail.hpp"
#include "Utils.hpp"

TrackTrail::TrackTrail(int spriteIndex, sf::Vector2f position, float rotation) :
AutoSprite({100.f, 100.f}, 0.f, {SpriteNames::effects2, 21, 21, 10000, false}), currentOpacity(155.f), deltaOpacity(currentOpacity/(60*(sprite.singleImageDurationMs/1000)))
{
    setOpacity(currentOpacity);
    setPosition(position, rotation);
}

void TrackTrail::updateDrawable() {
    AutoSprite::updateDrawable();
    currentOpacity -= deltaOpacity;
    setOpacity(round(currentOpacity));
}
