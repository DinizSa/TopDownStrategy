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

enum SoundNames { steadyTank, damagedTank, rotationGun };

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
    
public:
    static AssetManager* get();
    SpriteSheet* getSprite(SpriteNames spriteSheet);
    void playSound(SoundNames soundName);
    void stopSound(SoundNames soundName);
};
