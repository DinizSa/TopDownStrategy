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
    spriteSheets.insert_or_assign(SpriteNames::tracks, new SpriteSheet({8, 1, imagesPath + "tracksSprites.png", sf::Vector2f({42.f, 246.f})}));
    spriteSheets.insert_or_assign(SpriteNames::guns, new SpriteSheet({8, 1, imagesPath + "gunsSprites.png", sf::Vector2f({256.f, 256.f})}));
    spriteSheets.insert_or_assign(SpriteNames::hulls, new SpriteSheet({8, 1, imagesPath + "hullsSprites.png", sf::Vector2f({256.f, 256.f})}));
    spriteSheets.insert_or_assign(SpriteNames::effects, new SpriteSheet({7, 7, imagesPath + "effectsSprites.png", sf::Vector2f({266.f, 266.f})}));
    spriteSheets.insert_or_assign(SpriteNames::effects2, new SpriteSheet({6, 4, imagesPath + "effectsSprites2.png", sf::Vector2f({125.f, 128.f})}));
    spriteSheets.insert_or_assign(SpriteNames::shotEffect, new SpriteSheet({3, 3, imagesPath + "shotSprite.png", sf::Vector2f({93.f, 93.f})}));

    loadSoundBuffer(SoundNames::movingTank, "movingTank.mp3");
    loadSoundBuffer(SoundNames::damagedTank, "damagedTank.mp3");
    loadSoundBuffer(SoundNames::rotationGun, "rotateGun.mp3");
    loadSoundBuffer(SoundNames::rotationGunStart, "rotateGunStart.mp3");
    loadSoundBuffer(SoundNames::rotationGunMoving, "rotateGunMoving.mp3");
    loadSoundBuffer(SoundNames::rotationGunStop, "rotateGunStop.mp3");
    loadSoundBuffer(SoundNames::shellExplosion, "shellExplosion.mp3");
    loadSoundBuffer(SoundNames::tankShot, "tankShot.mp3");
    loadSoundBuffer(SoundNames::tankGunBlast, "tankGunBlast.mp3");
}
void AssetManager::loadSoundBuffer(SoundNames soundName, const std::string& fileName) {
    const static std::string soundsPrefix = "/Users/Shared/merda/PleaseTanks/sound/";
    auto buffer = new sf::SoundBuffer();
    if (!buffer->loadFromFile(soundsPrefix + fileName)) {
        std::cout << "Error loading sound: " << soundsPrefix + fileName << std::endl;
    }
    soundBuffers.insert_or_assign(soundName, buffer);
    
}
AssetManager::~AssetManager() {
    for (auto& sprite : spriteSheets) {
        delete sprite.second;
    }
    for (auto soundPair : sounds) {
        for (auto sound : soundPair.second) {
            delete sound;
        }
    }
    for (auto& soundBuffer : soundBuffers) {
        delete soundBuffer.second;
    }
}
SpriteSheet* AssetManager::getSprite(SpriteNames sprite) {
    return spriteSheets.at(sprite);
}

sf::Sound* AssetManager::getPlayingSound(SoundNames soundName, int audioPlayerId) {
    sf::SoundBuffer* soundBuffer = soundBuffers.at(soundName);
    std::vector<sf::Sound*>& soundsFromId = sounds[audioPlayerId];
    for (auto sound : soundsFromId) {
        if (sound->getStatus() == sf::Sound::Playing) {
            return sound;
        }
    }
    return nullptr;
}

sf::Sound* AssetManager::playSound(SoundNames soundName, int audioPlayerId) {
    sf::SoundBuffer* soundBuffer = soundBuffers.at(soundName);
    std::vector<sf::Sound*>& soundsFromId = sounds[audioPlayerId];
    for (auto sound : soundsFromId) {
        if (sound->getStatus() == sf::Sound::Stopped) {
            if (sound->getBuffer() != soundBuffer) {
                sound->setBuffer(*soundBuffers.at(soundName));
            }
            sound->play();
            return sound;
        }
    }
    
    sf::Sound* sound = new sf::Sound;
    sound->setBuffer(*soundBuffer);
    sound->play();
    soundsFromId.push_back(sound);
    return sound;
}

void AssetManager::stopSound(SoundNames soundName, int audioPlayerId) {
    sf::SoundBuffer* soundBuffer = soundBuffers.at(soundName);
    std::vector<sf::Sound*>& soundsFromId = sounds[audioPlayerId];
    for (auto sound : soundsFromId) {
        if (sound->getStatus() == sf::Sound::Playing) {
            if (sound->getBuffer() == soundBuffer) {
                sound->stop();
            }
        }
    }
}
