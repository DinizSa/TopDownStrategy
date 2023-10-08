//
//  VisionMask.hpp
//  PleaseTanks
//
//  Created by Diniz Sá on 08/10/2023.
//

#pragma once
#include <SFML/Graphics.hpp>
#include "PhysicsBody.hpp"
#include "CombatUnit.hpp"
#include "Utils.hpp"
#include <cmath>
#include <algorithm>

class VisionMask {
public:
    VisionMask(){
    }
    void update(const std::vector<CombatUnit*>& turnUnits, const std::vector<CombatUnit*>& nonTurnUnits) {
        image.create(1200, 800, sf::Color(0, 0, 0, 100));
        for (auto unit : turnUnits) {
            if (!unit->getMovementCollisions())
                continue;
            sf::Vector2f center = unit->getCenter();
            float radius = unit->getRadius()*6;
            int minX = static_cast<int>(floor(std::fmax(0, center.x - radius)));
            int maxX = static_cast<int>(floor(std::fmin(center.x + radius, 1200)));
            int minY = static_cast<int>(floor(std::fmax(0, center.y - radius)));
            int maxY = static_cast<int>(floor(std::fmin(center.y + radius, 800)));
            double distance;
            for (int i = minX; i < maxX; i++) {
                for (int j = minY; j < maxY; j++) {
                    sf::Color currentColor = image.getPixel(i, j);
                    if (currentColor.a == 0)
                        continue;
                    distance = std::sqrt(std::pow(i - center.x, 2) + std::pow(j - center.y, 2));
                    if (distance < radius) {
                        image.setPixel(i, j, sf::Color::Transparent);
                    }
                }
            }
        }
        
        for (auto unit : nonTurnUnits) {
            sf::Vector2f center = unit->getCenter();
            sf::Vector2<int> centerInt = {(int)floor(center.x), (int)floor(center.y)};
            sf::Color currentColor = image.getPixel(centerInt.x, centerInt.y);
            if (currentColor.a > 0) {
                unit->setVisible(false);
            }
        }

        texture.loadFromImage(image);
        sprite = sf::Sprite(texture);
    };
    void draw(sf::RenderWindow& window){
        window.draw(sprite);
    };
private:
    sf::Image image;
    sf::Texture texture;
    sf::Sprite sprite;
};
