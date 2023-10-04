//
//  Sprite.hpp
//  PleaseTanks
//
//  Created by Diniz Sá on 23/09/2023.
//

#pragma once

enum SpriteNames { tracks, hulls, guns, effects, effects2, darkExplosion, mine, tree, soldierFeet, soldierMove, soldierReload, soldierShoot, soldierGrenade, grenade, smoke, smokeDense, blood};

struct Sprite {
    SpriteNames spriteName;
    int minIndex;
    int maxIndex;
    int singleImageDurationMs;
    bool loop;
    int loopsUntilCleanup;
    std::function<void()> endCallback;
    
    Sprite(SpriteNames spriteName, int minIndex, int maxIndex, int singleImageDurationMs, bool loop, int loopsUntilCleanup = 0, std::function<void()> endCallback = [](){}): spriteName(spriteName), minIndex(minIndex), maxIndex(maxIndex), singleImageDurationMs(singleImageDurationMs), loop(loop), endCallback(endCallback), loopsUntilCleanup(loopsUntilCleanup) {};
};
