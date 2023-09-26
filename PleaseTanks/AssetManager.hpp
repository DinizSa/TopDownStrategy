//
//  AssetManager.hpp
//  PleaseTanks
//
//  Created by Diniz Sá on 19/09/2023.
//

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <unordered_map>
#include <vector>

#include "SpriteSheet.hpp"

enum SoundNames { steadyTank, damagedTank, rotationGun, rotationGunStart, rotationGunMoving, rotationGunStop };

class AssetManager {
private:
    std::unordered_map<SpriteNames, SpriteSheet*> spriteSheets;
    
    std::unordered_map<SoundNames, sf::SoundBuffer*> soundBuffers;
    std::vector<sf::Sound*> sounds;

private:
    AssetManager();
    ~AssetManager();
    void operator=(const AssetManager&) = delete;
    AssetManager(AssetManager& other) = delete;
    
    void loadSoundBuffer(SoundNames soundName, const std::string& fileName);
    
public:
    static AssetManager* get();
    SpriteSheet* getSprite(SpriteNames spriteSheet);
    sf::Sound* playSound(SoundNames soundName);
    void stopSound(SoundNames soundName);
};
