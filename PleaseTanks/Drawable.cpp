//
//  Hull.cpp
//  PleaseTanks
//
//  Created by Diniz Sá on 14/09/2023.
//

#include "Drawable.hpp"
#include <cmath>

Drawable::Drawable(sf::Vector2<float> size, sf::Vector2<float> deltaCenter, const std::string&& texturePath) : deltaCenter(deltaCenter) {
    
    rect.setSize({size.x, size.y});
    if (!texture.loadFromFile(texturePath)) {
        std::cout << "Error loading texture. Path: " << texturePath << " \n";
    }
    rect.setTexture(&texture);
    setRotationCenter({size.x/2.f, size.y/2});
    
    translate(-deltaCenter);
}

void Drawable::setRotationCenter(sf::Vector2<float>&& center) {
    rect.setOrigin({center.x, center.y});
}
float Drawable::getRotation() {
    return rect.getRotation();
}
void Drawable::translate(float delta) {
    float rot = rect.getRotation();
    float rotDeg = rot * M_PI / 180;
    float x = -delta * sin(rotDeg);
    float y = delta * cos(rotDeg);
    translate({x, y});
}
void Drawable::translate(float delta, float angle) {
    float rotDeg = angle * M_PI / 180;
    float x = -delta * sin(rotDeg);
    float y = delta * cos(rotDeg);
    translate({x, y});
}
void Drawable::translate(sf::Vector2<float> delta) {
    delta += rect.getPosition();
    rect.setPosition(delta);
}
void Drawable::rotate(float deltaAngle) {
    rect.rotate(deltaAngle);
}
void Drawable::rotateAroundParent(float currentAngle, float deltaAngle) {
    float rot0 = currentAngle;
    sf::Transform t0;
    t0.rotate(rot0, deltaCenter);
    auto p0 = t0.transformPoint(0.f, 0.f);
    
    sf::Transform t1;
    t1.rotate(rot0 + deltaAngle, deltaCenter);
    auto p1 = t1.transformPoint(0.f, 0.f);
    auto p2 = p1 - p0;
    
    rect.rotate(deltaAngle);
    translate(p2);
}

void Drawable::draw(sf::RenderWindow& window) {
    window.draw(rect);
}
