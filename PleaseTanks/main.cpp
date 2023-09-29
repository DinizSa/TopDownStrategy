#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
#include <ctime>
#include <thread>

#include "Tank.hpp"
#include "Projectile.hpp"
#include "TileMap.hpp"
#include "Mine.hpp"
#include "StaticEnvironment.hpp"
#include "Utils.hpp"

int main()
{
    
    
    int windowWidth = 1200;
    int windowHeight = 800;
    sf::Vector2f windowDimensions = {(float)windowWidth, (float)windowHeight };
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Please Tanks");
    
    sf::Vector2f size = {100.f, 100.f};
    sf::Vector2f position = {200.f, 200.f};
    Tank tank = Tank(size, position);
    
    sf::Vector2f position2 = {800.f, 250.f};
    Tank tank2 = Tank(size, position2);
    
    bool forwardPressed = false;
    bool turnClockPressed = false;
    bool turnAnticlockPressed = false;
    bool backwardPressed = false;
    bool turnClockGunPressed = false;
    bool turnAnticlockGunPressed = false;
    
    sf::Text framesText;
    framesText.setCharacterSize(30);
    sf::Font font;
    font.loadFromFile("/Users/Shared/merda/PleaseTanks/fonts/Drunk & Proud.otf");
    framesText.setFont(font);
    framesText.setPosition(50.f, 50.f);
    framesText.setFillColor(sf::Color(255, 0, 0));
    int frames = 0;
    const int fps = 60;
    const int secondsMs = pow(10, 3);
    
    using clock = std::chrono::steady_clock;
    
    std::chrono::time_point<clock> next_frame = clock::now();
    
//    sf::Vector2f velocity = {0.5f, 0.2f};
//    tank2.setVelocity(velocity);
    
    const int terrainMap[] =
    {
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
    };
    TileMap terrain;
    int tilesRow = 8;
    int tilesColumn = 8;
    terrain.load("/Users/Shared/merda/PleaseTanks/images/grassTiled.png", sf::Vector2u(windowWidth/tilesRow, windowWidth/tilesColumn), terrainMap, tilesRow, tilesColumn);
    
    new BasicMine({200.f, 600.f}, {40.f, 40.f});
    new Tree({120.f, 120.f}, {300.f, 350.f});
    new Tree({120.f, 120.f}, {450.f, 300.f});
    new Tree({130.f, 130.f}, {600.f, 350.f});
    
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::MouseButtonPressed){
                if (event.mouseButton.button == sf::Mouse::Left) {
                    std::cout << "click: " << event.mouseButton.x << ", " << event.mouseButton.y << std::endl;
                    sf::Vector2f point = {(float)event.mouseButton.x, (float)event.mouseButton.y};
//                    tank.contains(point);
//                    tank2.contains(point);
//                    std::vector<sf::Vector2f> pointsPath = Utils::getPathPoints(&tank.hull, point);
//                    std::cout << "path: \n";
//                    for (auto& point: pointsPath) {
//                        std::cout << point.x << ", " << point.y << std::endl;
//                    }
                    tank.travelToDestination(point);
                }
            }
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed) {
                switch (event.key.scancode) {
                    case sf::Keyboard::Scan::Escape:
                        window.close();
                        break;
                    case sf::Keyboard::Scan::W:
                        forwardPressed = true;
                        break;
                    case sf::Keyboard::Scan::S:
                        backwardPressed = true;
                        break;
                    case sf::Keyboard::Scan::A:
                        turnAnticlockPressed = true;
                        break;
                    case sf::Keyboard::Scan::D:
                        turnClockPressed = true;
                        break;
                    case sf::Keyboard::Scan::E:
                        turnClockGunPressed = true;
                        break;
                    case sf::Keyboard::Scan::Q:
                        turnAnticlockGunPressed = true;
                        break;
                    case sf::Keyboard::Scan::Space:
                        tank.shot();
                        break;
                    default:
                        break;
                }
            }
            if (event.type == sf::Event::KeyReleased) {
                switch (event.key.scancode) {
                    case sf::Keyboard::Scan::W:
                        forwardPressed = false;
                        break;
                    case sf::Keyboard::Scan::S:
                        backwardPressed = false;
                        break;
                    case sf::Keyboard::Scan::A:
                        turnAnticlockPressed = false;
                        break;
                    case sf::Keyboard::Scan::D:
                        turnClockPressed = false;
                        break;
                    case sf::Keyboard::Scan::E:
                        turnClockGunPressed = false;
                        break;
                    case sf::Keyboard::Scan::Q:
                        turnAnticlockGunPressed = false;
                        break;
                    default:
                        break;
                }
            }
        }

        if (forwardPressed){
            tank.moveFront();
        }
        if (backwardPressed)
            tank.moveBack();
        if (turnClockPressed)
            tank.rotateClock();
        if (turnAnticlockPressed)
            tank.rotateAntiClock();
        if (turnClockGunPressed)
            tank.rotateGunClock();
        if (turnAnticlockGunPressed)
            tank.rotateGunAntiClock();
        
        tank.update();
//        tank2.update();
        
        Drawable::updateDrawables();
        AutoSprite::updateAutoSprites();
        PhysicsBody::updatePhysicsBodys();
        
        window.clear();
        
        window.draw(terrain);
        Drawable::drawAll(window);
        window.draw(framesText);
        window.display();
        
        next_frame += std::chrono::milliseconds(secondsMs / fps);
        std::this_thread::sleep_until(next_frame);
        framesText.setString(std::to_string(frames));
        frames++;
    }

    return 0;
}
