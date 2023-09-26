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

    loadSoundBuffer(SoundNames::steadyTank, "steadyTank.mp3");
    loadSoundBuffer(SoundNames::damagedTank, "damagedTank.mp3");
    loadSoundBuffer(SoundNames::rotationGun, "rotateGun.mp3");
    loadSoundBuffer(SoundNames::rotationGunStart, "rotateGunStart.mp3");
    loadSoundBuffer(SoundNames::rotationGunMoving, "rotateGunMoving.mp3");
    loadSoundBuffer(SoundNames::rotationGunStop, "rotateGunStop.mp3");
}
void AssetManager::loadSoundBuffer(SoundNames soundName, const std::string& fileName) {
    const static std::string soundsPrefix = "/Users/Shared/merda/PleaseTanks/sound/";
    auto buffer = new sf::SoundBuffer();
    auto oi = soundsPrefix + fileName;
    if (!buffer->loadFromFile(oi)) {
        std::cout << "Error loading sound: " << oi << std::endl;
    }
    soundBuffers.insert_or_assign(soundName, buffer);
    
}
AssetManager::~AssetManager() {
    for (auto& sprite : spriteSheets) {
        delete sprite.second;
    }
    for (auto& soundBuffer : soundBuffers) {
        delete soundBuffer.second;
    }
}
SpriteSheet* AssetManager::getSprite(SpriteNames sprite) {
    return spriteSheets.at(sprite);
}

sf::Sound* AssetManager::playSound(SoundNames soundName) {
    sf::SoundBuffer* soundBuffer = soundBuffers.at(soundName);
    for (auto sound : sounds) {
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
    sounds.push_back(sound);
    return sound;
}

void AssetManager::stopSound(SoundNames soundName) {
    sf::SoundBuffer* soundBuffer = soundBuffers.at(soundName);
    for (auto sound : sounds) {
        if (sound->getStatus() == sf::Sound::Playing) {
            if (sound->getBuffer() == soundBuffer) {
                sound->stop();
            }
        }
    }
}
