//
//  Sprite.hpp
//  PleaseTanks
//
//  Created by Diniz Sá on 23/09/2023.
//

#pragma once

enum SpriteNames { tracks, hulls, guns, effects, effects2, shotEffect, mine, tree, soldierFeet, soldierSprite};

struct Sprite {
    SpriteNames spriteName;
    int minIndex;
    int maxIndex;
    int singleImageDurationMs;
    bool loop;
    
    Sprite(SpriteNames spriteName, int minIndex, int maxIndex, int singleImageDurationMs, bool loop): spriteName(spriteName), minIndex(minIndex), maxIndex(maxIndex), singleImageDurationMs(singleImageDurationMs), loop(loop) {};
};
