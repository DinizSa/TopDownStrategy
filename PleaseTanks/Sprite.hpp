//
//  Sprite.hpp
//  PleaseTanks
//
//  Created by Diniz Sá on 23/09/2023.
//

#pragma once

enum SpriteNames { tracks, hulls, guns, effects, effects2, shotEffect, mine};

struct Sprite {
    SpriteNames spriteName;
    int minIndex;
    int maxIndex;
    int singleImageDurationMs;
    bool loop;
};
