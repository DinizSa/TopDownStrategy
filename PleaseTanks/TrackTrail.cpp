//
//  Track.cpp
//  PleaseTanks
//
//  Created by Diniz Sá on 14/09/2023.
//

#include "TrackTrail.hpp"
#include "Utils.hpp"

TrackTrail::TrackTrail(sf::Vector2f size, int spriteIndex, sf::Vector2f position, float rotation) :
AutoSprite(size, 0.f, {SpriteNames::effects2, 21, 21, 5000, false}), currentOpacity(155.f), deltaOpacity(currentOpacity/(60*(sprite.singleImageDurationMs/1000)))
{
    setOpacity(currentOpacity);
    setPosition(position, rotation);
}

void TrackTrail::updateDrawable() {
    AutoSprite::updateDrawable();
    currentOpacity -= deltaOpacity;
    setOpacity(round(currentOpacity));
}
