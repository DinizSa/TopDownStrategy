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
    sprites.insert_or_assign(SpriteNames::tracks, new Sprite({8, 1, "/Users/Shared/merda/PleaseTanks/images/tracksSprites.png", sf::Vector2f({42.f, 246.f})}));
    sprites.insert_or_assign(SpriteNames::guns, new Sprite({8, 1, "/Users/Shared/merda/PleaseTanks/images/gunsSprites.png", sf::Vector2f({256.f, 256.f})}));
    sprites.insert_or_assign(SpriteNames::hulls, new Sprite({8, 1, "/Users/Shared/merda/PleaseTanks/images/hullsSprites.png", sf::Vector2f({256.f, 256.f})}));
    sprites.insert_or_assign(SpriteNames::effects, new Sprite({8, 7, "/Users/Shared/merda/PleaseTanks/images/hullsSprites.png", sf::Vector2f({266.f, 266.f})}));
}
AssetManager::~AssetManager() {
    for (auto& sprite : sprites) {
        delete sprite.second;
    }
}
Sprite* AssetManager::getSprite(SpriteNames sprite) {
    return sprites.at(sprite);
}
