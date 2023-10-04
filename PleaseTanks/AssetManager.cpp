//
//  AssetManager.cpp
//  PleaseTanks
//
//  Created by Diniz Sá on 19/09/2023.
//

#include "AssetManager.hpp"
#include <iostream>

AssetManager* AssetManager::get() {
    static AssetManager instance = AssetManager();
    return &instance;
}
AssetManager::AssetManager() {
    const std::string imagesPath = "/Users/Shared/merda/PleaseTanks/images/";
    spriteSheets.insert_or_assign(SpriteNames::tracks, new SpriteSheet({8, 1, imagesPath + "tracksSprites.png", sf::Vector2f({42.f, 246.f}), 1.f}));
    spriteSheets.insert_or_assign(SpriteNames::guns, new SpriteSheet({8, 1, imagesPath + "gunsSprites.png", sf::Vector2f({256.f, 256.f}), 1.f}));
    spriteSheets.insert_or_assign(SpriteNames::hulls, new SpriteSheet({8, 1, imagesPath + "hullsSprites.png", sf::Vector2f({256.f, 256.f}), 1.f}));
    spriteSheets.insert_or_assign(SpriteNames::effects, new SpriteSheet({7, 7, imagesPath + "effectsSprites.png", sf::Vector2f({266.f, 266.f}), 1.f}));
    spriteSheets.insert_or_assign(SpriteNames::effects2, new SpriteSheet({6, 4, imagesPath + "effectsSprites2.png", sf::Vector2f({125.f, 128.f}), 1.f}));
    spriteSheets.insert_or_assign(SpriteNames::darkExplosion, new SpriteSheet({3, 3, imagesPath + "darkExplosion.png", sf::Vector2f({93.f, 93.f}), 1.f}));
    spriteSheets.insert_or_assign(SpriteNames::mine, new SpriteSheet({1, 1, imagesPath + "mine.png", sf::Vector2f({256.f, 256.f}), 1.f}));
    spriteSheets.insert_or_assign(SpriteNames::tree, new SpriteSheet({1, 1, imagesPath + "tree.png", sf::Vector2f({100.f, 100.f}), 1.f}));
    spriteSheets.insert_or_assign(SpriteNames::soldierFeet, new SpriteSheet({6, 4, imagesPath + "soldierFeet.png", sf::Vector2f({124.f, 204.f}), 1.f}));
    spriteSheets.insert_or_assign(SpriteNames::soldierMove, new SpriteSheet({5, 4, imagesPath + "soldierMove.png", sf::Vector2f({96.f, 150.f}), 0.96f}));
    spriteSheets.insert_or_assign(SpriteNames::soldierReload, new SpriteSheet({5, 4, imagesPath + "soldierReload.png", sf::Vector2f({101.f, 154.f}), 1.f}));
    spriteSheets.insert_or_assign(SpriteNames::soldierShoot, new SpriteSheet({3, 1, imagesPath + "soldierShoot.png", sf::Vector2f({95.f, 149.f}), 0.96f}));
    spriteSheets.insert_or_assign(SpriteNames::soldierGrenade, new SpriteSheet({4, 2, imagesPath + "soldierGrenade.png", sf::Vector2f({115.f, 149.f}), 0.96f}));
    spriteSheets.insert_or_assign(SpriteNames::grenade, new SpriteSheet({1, 1, imagesPath + "grenade.png", sf::Vector2f({256.f, 256.f}), 1.f}));
    spriteSheets.insert_or_assign(SpriteNames::smoke, new SpriteSheet({4, 4, imagesPath + "smoke.png", sf::Vector2f({256.f, 256.f}), 1.f}));
    spriteSheets.insert_or_assign(SpriteNames::smokeDense, new SpriteSheet({4, 4, imagesPath + "smokeDense.png", sf::Vector2f({256.f, 256.f}), 1.f}));
    spriteSheets.insert_or_assign(SpriteNames::blood, new SpriteSheet({6, 1, imagesPath + "blood.png", sf::Vector2f({128.f, 128.f}), 1.f}));

    loadSoundBuffer(SoundNames::movingTank, "movingTank.mp3");
    loadSoundBuffer(SoundNames::damagedTank, "damagedTank.mp3");
    loadSoundBuffer(SoundNames::rotationGun, "rotateGun.mp3");
    loadSoundBuffer(SoundNames::rotationGunStart, "rotateGunStart.mp3");
    loadSoundBuffer(SoundNames::rotationGunMoving, "rotateGunMoving.mp3");
    loadSoundBuffer(SoundNames::rotationGunStop, "rotateGunStop.mp3");
    loadSoundBuffer(SoundNames::shellExplosion, "shellExplosion.mp3");
    loadSoundBuffer(SoundNames::tankShot, "tankShot.mp3");
    loadSoundBuffer(SoundNames::tankGunBlast, "tankGunBlast.mp3");
    loadSoundBuffer(SoundNames::rifle, "rifle.mp3");
    loadSoundBuffer(SoundNames::bulletHitMetal, "bulletHitMetal.mp3");
    loadSoundBuffer(SoundNames::rifleReload, "rifleReload.mp3");
    loadSoundBuffer(SoundNames::grenadeExplosion, "grenadeExplosion.mp3");
    loadSoundBuffer(SoundNames::grenadePinPull, "grenadePinPull.mp3");
    loadSoundBuffer(SoundNames::grenadeThrow, "grenadeThrow.mp3");
    loadSoundBuffer(SoundNames::bigExplosion, "bigExplosion.mp3");
    loadSoundBuffer(SoundNames::hurt, "hurt.mp3");
    loadSoundBuffer(SoundNames::smokeGrenade, "smokeGrenade.mp3");
    loadSoundBuffer(SoundNames::smokeGrenadeLaunch, "smokeGrenadeLaunch.mp3");
}
void AssetManager::loadSoundBuffer(SoundNames soundName, const std::string& fileName) {
    const static std::string soundsPrefix = "/Users/Shared/merda/PleaseTanks/sound/";
    std::shared_ptr<sf::SoundBuffer> buffer = std::make_shared<sf::SoundBuffer>();
    if (!buffer->loadFromFile(soundsPrefix + fileName)) {
        std::cout << "Error loading sound: " << soundsPrefix + fileName << std::endl;
        return;
    }
    soundBuffers.insert_or_assign(soundName, buffer);
    
}
AssetManager::~AssetManager() {
    for (auto& sprite : spriteSheets) {
        delete sprite.second;
    }
    for (auto soundPair : soundsPool) {
        for (auto sound : soundPair.second) {
            delete sound;
        }
    }
    
    soundBuffers.clear();
//    for (auto& soundBuffer : soundBuffers) {
//        delete soundBuffer.second;
//    }
    
}
SpriteSheet* AssetManager::getSprite(SpriteNames sprite) {
    return spriteSheets.at(sprite);
}

sf::Sound* AssetManager::getPlayingSound(SoundNames soundName, int audioPlayerId) {
    std::vector<sf::Sound*>& soundsFromId = soundsPool[audioPlayerId];
    for (auto sound : soundsFromId) {
        if (sound->getStatus() == sf::Sound::Playing) {
            return sound;
        }
    }
    return nullptr;
}

sf::Sound* AssetManager::playSound(Sound sound, int audioPlayerId) {
    sf::Sound* s = playSound(sound.name, audioPlayerId);
    s->setVolume(sound.volume);
    s->setLoop(sound.loop);
    return s;
}
sf::Sound* AssetManager::playSound(SoundNames soundName, int audioPlayerId) {
    std::vector<sf::Sound*>& soundsFromId = soundsPool[audioPlayerId];
    for (auto sound : soundsFromId) {
        if (sound->getStatus() == sf::Sound::Stopped) {
            if (sound->getBuffer() != soundBuffers.at(soundName).get()) {
                sound->setBuffer(*soundBuffers.at(soundName));
            }
            sound->play();
            return sound;
        }
    }
    
    sf::Sound* sound = new sf::Sound;
    sound->setBuffer(*soundBuffers.at(soundName));
    sound->play();
    soundsFromId.push_back(sound);
    return sound;
}

void AssetManager::stopSound(SoundNames soundName, int audioPlayerId) {
    std::vector<sf::Sound*>& soundsFromId = soundsPool[audioPlayerId];
    for (auto sound : soundsFromId) {
        if (sound->getStatus() == sf::Sound::Playing) {
            if (sound->getBuffer() == soundBuffers.at(soundName).get()) {
                sound->stop();
            }
        }
    }
}
