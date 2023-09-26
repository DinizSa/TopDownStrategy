//
//  AssetManager.cpp
//  PleaseTanks
//
//  Created by Diniz Sá on 19/09/2023.
//

#include "AssetManager.hpp"

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
    
    const std::string soundsPrefix = "/Users/Shared/merda/PleaseTanks/sound/";
    
    auto steadyTankBuffer = new sf::SoundBuffer();
    steadyTankBuffer->loadFromFile(soundsPrefix + "steadyTank.mp3");
    soundBuffers.insert_or_assign(SoundNames::steadyTank, steadyTankBuffer);
    
    auto damagedTankBuffer = new sf::SoundBuffer();
    damagedTankBuffer->loadFromFile(soundsPrefix + "damagedTank.mp3");
    soundBuffers.insert_or_assign(SoundNames::damagedTank, damagedTankBuffer);
    
    auto rotateGunBuffer = new sf::SoundBuffer();
    rotateGunBuffer->loadFromFile(soundsPrefix + "rotateGun.mp3");
    soundBuffers.insert_or_assign(SoundNames::rotationGun, rotateGunBuffer);
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

void AssetManager::playSound(SoundNames soundName) {
    sf::SoundBuffer* soundBuffer = soundBuffers.at(soundName);
    for (auto sound : sounds) {
        if (sound->getStatus() == sf::Sound::Stopped) {
            if (sound->getBuffer() != soundBuffer) {
                sound->setBuffer(*soundBuffers.at(soundName));
            }
            sound->play();
            return;
        }
    }
    
    sf::Sound* sound = new sf::Sound;
    sound->setBuffer(*soundBuffer);
    sound->play();
    sounds.push_back(sound);
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
