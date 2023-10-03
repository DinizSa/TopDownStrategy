//
//  Sprite.hpp
//  PleaseTanks
//
//  Created by Diniz Sá on 23/09/2023.
//

#pragma once

enum SoundNames { movingTank, damagedTank, rotationGun, rotationGunStart, rotationGunMoving, rotationGunStop, shellExplosion, tankShot, idleTank, tankGunBlast, rifle, bulletHitMetal, rifleReload, grenadeExplosion, grenadePinPull, grenadeThrow, bigExplosion, hurt };

struct Sound {
    SoundNames name;
    float volume;
    bool loop;
    
    Sound(SoundNames name, float volume, bool loop): name(name), volume(volume), loop(loop) {}
};
