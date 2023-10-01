//
//  Sprite.hpp
//  PleaseTanks
//
//  Created by Diniz Sá on 23/09/2023.
//

#pragma once

enum SpriteNames { tracks, hulls, guns, effects, effects2, shotEffect, mine, tree, soldierFeet, soldierMove, soldierReload, soldierShoot };

struct Sprite {
    SpriteNames spriteName;
    int minIndex;
    int maxIndex;
    int singleImageDurationMs;
    bool loop;
    std::function<void()> endCallback;
    
    Sprite(SpriteNames spriteName, int minIndex, int maxIndex, int singleImageDurationMs, bool loop, std::function<void()> endCallback = [](){}): spriteName(spriteName), minIndex(minIndex), maxIndex(maxIndex), singleImageDurationMs(singleImageDurationMs), loop(loop), endCallback(endCallback) {};
};
