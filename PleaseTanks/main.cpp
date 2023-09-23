#include <SFML/Graphics.hpp>

#include <iostream>
#include <ctime>
#include <thread>

#include "Tank.hpp"

int main()
{
    
    
    int windowWidth = 1000;
    int windowHeight = 1000;
    sf::Vector2f windowDimensions = {(float)windowWidth, (float)windowHeight };
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Please Tanks");
    
    sf::Vector2f size = {200.f, 200.f};
    sf::Vector2f position = {200.f, 200.f};
    Tank tank = Tank(size, position);
    
    sf::Vector2f position2 = {200.f, 450.f};
    Tank tank2 = Tank(size, position2);
    
    sf::RectangleShape bg;
    sf::Texture textureBg;
    textureBg.loadFromFile("/Users/Shared/merda/PleaseTanks/images/grass.png");
    bg.setTexture(&textureBg);
    bg.setSize(windowDimensions);
    
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
    
    sf::Vector2f velocity = {0.5f, 0.5f};
    tank2.setVelocity(velocity);
    
    
    
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::MouseButtonPressed){
                if (event.mouseButton.button == sf::Mouse::Left) {
                    std::cout << event.mouseButton.x << ", " << event.mouseButton.y << std::endl;
                    sf::Vector2f point = {(float)event.mouseButton.x, (float)event.mouseButton.y};
                    tank.contains(point);
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

        if (forwardPressed)
            tank.moveFront();
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
        tank2.update();
        
        Drawable::updateDrawables();
        
        window.clear();
        
        window.draw(bg);
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
