#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
#include <ctime>
#include <thread>

#include "Tank.hpp"
#include "Projectile.hpp"
#include "TileMap.hpp"
#include "StaticEnvironment.hpp"
#include "Utils.hpp"
#include "CombatUnit.hpp"
#include "Configs.hpp"
#include "Weapon.hpp"
#include "HullParams.hpp"
#include "GunParams.hpp"
#include "Gameplay.hpp"
#include "UnitHud.hpp"

#define ASIO_STANDALONE
#include <asio.hpp>
#include <asio/ts/buffer.hpp>
#include <asio/ts/internet.hpp>

int main()
{
//    asio::error_code ec;
//    asio::io_context context;
//    asio::ip::tcp::endpoint endpoint(asio::ip::make_address("93.184.216.34", ec), 80);
//    asio::ip::tcp::socket socket(context);
//
//    socket.connect(endpoint, ec);
//    if (!ec) {
//        std::cout << "Connected! \n";
//    } else {
//        std::cout << "Error connecting: " << ec.message() << " \n";
//    }
    
    int fps = CONFIGS::FPS;
    int windowWidth = 1200;
    int windowHeight = 800;
    sf::Vector2f windowDimensions = {(float)windowWidth, (float)windowHeight };
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Please Tanks");
    
    Gameplay gameplay;
    
    
    
    bool forwardPressed = false;
    bool turnClockPressed = false;
    bool turnAnticlockPressed = false;
    bool backwardPressed = false;
    bool turnClockGunPressed = false;
    bool turnAnticlockGunPressed = false;
    bool attackPrimary = false;
    bool attackSecondary = false;
    
    sf::Text framesText;
    framesText.setCharacterSize(30);
    sf::Font font = AssetManager::get()->getFont();
    framesText.setFont(font);
    framesText.setPosition(50.f, 50.f);
    framesText.setFillColor(sf::Color(255, 0, 0));
    int frames = 0;
    const int secondsMs = pow(10, 3);
    
    sf::Text playerATurnText, playerBTurnText, pausedText;
    playerATurnText.setCharacterSize(40);
    playerATurnText.setFont(font);
    playerATurnText.setPosition(320.f, 30.f);
    playerATurnText.setFillColor(sf::Color(255, 0, 0));
    playerATurnText.setString("Player A");
    playerBTurnText.setCharacterSize(40);
    playerBTurnText.setFont(font);
    playerBTurnText.setPosition(720.f, 30.f);
    playerBTurnText.setFillColor(sf::Color(0, 0, 255));
    playerBTurnText.setString("Player B");
    pausedText.setCharacterSize(50);
    pausedText.setFont(font);
    pausedText.setPosition(1000.f, 30.f);
    pausedText.setFillColor(sf::Color(255, 255, 255));
    pausedText.setString("Paused");
    
    
    using clock = std::chrono::steady_clock;
    
    std::chrono::time_point<clock> next_frame = clock::now();
    
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
    
    auto mine = std::make_shared<Weapon>(MineAntiTank());
    new Projectile({200.f, 700.f}, 0.f, 0.f, mine);
    
    new Tree({120.f, 120.f}, {300.f, 350.f});
    new Tree({120.f, 120.f}, {450.f, 300.f});
    new Tree({130.f, 130.f}, {600.f, 350.f});
    
    UnitHud unitHud;
    
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::MouseButtonPressed){
                if (event.mouseButton.button == sf::Mouse::Left) {
                    std::cout << "click: " << event.mouseButton.x << ", " << event.mouseButton.y << std::endl;
                    sf::Vector2f point = {(float)event.mouseButton.x, (float)event.mouseButton.y};
                    gameplay.handleClick(point);
                    
                    unitHud.handleClick(point);
                    
                    const CombatUnit* selectedUnit = gameplay.getSelected();
                    unitHud.setSelectedUnit(selectedUnit);
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
                    case sf::Keyboard::Scan::N:
                        attackPrimary = true;
                        break;
                    case sf::Keyboard::Scan::M:
                        attackSecondary = true;
                        break;
                    case sf::Keyboard::Scan::P:
                        gameplay.togglePause();
                        break;
                    case sf::Keyboard::Scan::Space:
                        gameplay.togglePlayTurn();
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
                    case sf::Keyboard::Scan::N:
                        attackPrimary = false;
                        break;
                    case sf::Keyboard::Scan::M:
                        attackSecondary = false;
                        break;
                    default:
                        break;
                }
            }
        }
        
        if (gameplay.getPlayerTurn() == Gameplay::PlayerTurn::playerA) {
            playerATurnText.setFillColor(sf::Color(255, 0, 0, 255));
            playerBTurnText.setFillColor(sf::Color(0, 0, 255, 100));
        } else {
            playerATurnText.setString("Player B");
            playerATurnText.setFillColor(sf::Color(0, 0, 255, 100));
            playerBTurnText.setFillColor(sf::Color(255, 0, 0, 255));
        }

        PressedButtons buttons {
            forwardPressed,
            backwardPressed,
            turnClockPressed,
            turnAnticlockPressed,
            turnClockGunPressed,
            turnAnticlockGunPressed,
            attackPrimary,
            attackSecondary
        };
        gameplay.handleControls(buttons);

        Drawable::updateDrawables();
        PhysicsBody::updatePhysicsBodys();
        
        window.clear();
        
        window.draw(terrain);
        Drawable::drawAll(window);
        window.draw(framesText);
        window.draw(playerATurnText);
        window.draw(playerBTurnText);
        unitHud.draw(window);
    
        gameplay.update();
        gameplay.draw(window);

        if (gameplay.isPaused())
            window.draw(pausedText);
        window.display();
        
        next_frame += std::chrono::milliseconds(secondsMs / fps);
        std::this_thread::sleep_until(next_frame);
        framesText.setString(std::to_string(frames));
        frames++;
    }

    return 0;
}
