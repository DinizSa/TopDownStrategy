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
    spriteSheets.insert_or_assign(SpriteNames::tracks, new SpriteSheet({8, 1, "/Users/Shared/merda/PleaseTanks/images/tracksSprites.png", sf::Vector2f({42.f, 246.f})}));
    spriteSheets.insert_or_assign(SpriteNames::guns, new SpriteSheet({8, 1, "/Users/Shared/merda/PleaseTanks/images/gunsSprites.png", sf::Vector2f({256.f, 256.f})}));
    spriteSheets.insert_or_assign(SpriteNames::hulls, new SpriteSheet({8, 1, "/Users/Shared/merda/PleaseTanks/images/hullsSprites.png", sf::Vector2f({256.f, 256.f})}));
    spriteSheets.insert_or_assign(SpriteNames::effects, new SpriteSheet({7, 7, "/Users/Shared/merda/PleaseTanks/images/effectsSprites.png", sf::Vector2f({266.f, 266.f})}));
    spriteSheets.insert_or_assign(SpriteNames::effects2, new SpriteSheet({6, 4, "/Users/Shared/merda/PleaseTanks/images/effectsSprites2.png", sf::Vector2f({125.f, 128.f})}));
    spriteSheets.insert_or_assign(SpriteNames::shotEffect, new SpriteSheet({3, 3, "/Users/Shared/merda/PleaseTanks/images/shotSprite.png", sf::Vector2f({93.f, 93.f})}));
}
AssetManager::~AssetManager() {
    for (auto& sprite : spriteSheets) {
        delete sprite.second;
    }
}
SpriteSheet* AssetManager::getSprite(SpriteNames sprite) {
    return spriteSheets.at(sprite);
}
