//
//  AssetManager.hpp
//  PleaseTanks
//
//  Created by Diniz Sá on 19/09/2023.
//

#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>

#include "Sprite.hpp"

enum SpriteNames { tracks, hulls, guns};

class AssetManager {
private:
    std::unordered_map<SpriteNames, Sprite*> sprites;
    
private:
    AssetManager();
    ~AssetManager();
    void operator=(const AssetManager&) = delete;
    AssetManager(AssetManager& other) = delete;
    
public:
    static AssetManager* get();
    Sprite* getSprite(SpriteNames sprite);
};
