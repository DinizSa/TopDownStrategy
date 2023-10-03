//
//  Track.cpp
//  PleaseTanks
//
//  Created by Diniz Sá on 14/09/2023.
//

#include "TrackTrail.hpp"
#include "Utils.hpp"
#include "Configs.hpp"

TrackTrail::TrackTrail(sf::Vector2f size, int spriteIndex, sf::Vector2f position, float rotation) :
AutoSprite(size, 0.f, {SpriteNames::effects2, 21, 21, 5000, false}), currentOpacity(155.f), deltaOpacity(currentOpacity/(CONFIGS::FPS * (sprite.singleImageDurationMs/1000)))
{
    setOpacity(currentOpacity);
    setPosition(position, rotation);
}

TrackTrail::~TrackTrail(){
}

void TrackTrail::updateDrawable() {
    AutoSprite::updateDrawable();
    currentOpacity -= deltaOpacity;
    int newOpacity = round(currentOpacity);
    if (newOpacity <= 0){
        dirty = true;
    }
    setOpacity(newOpacity);
}
