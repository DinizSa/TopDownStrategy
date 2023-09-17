#include <SFML/Graphics.hpp>

#include <iostream>

#include "Tank.hpp"

int main()
{
    int windowWidth = 600;
    int windowHeight = 600;
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Please Tanks");
    
    
    Tank tank = Tank({200.f, 200.f});

    sf::Vector2<float> size = {200.f, 200.f};
    sf::Vector2<float> position = {200.f, 200.f};
    Tank tank = Tank(size, position);
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed) {
                switch (event.key.scancode) {
                    case sf::Keyboard::Scan::Escape:
                        window.close();
                        break;
                    case sf::Keyboard::Scan::E:
                        tank.rotateGunClock();
                        break;
                    case sf::Keyboard::Scan::Q:
                        tank.rotateGunAntiClock();
                        break;
                    case sf::Keyboard::Scan::A:
                        tank.rotateAntiClock();
                        break;
                    case sf::Keyboard::Scan::D:
                        tank.rotateClock();
                        break;
                    case sf::Keyboard::Scan::S:
                        tank.moveBack();
                        break;
                    case sf::Keyboard::Scan::W:
                        tank.moveFront();
                        break;
                    default:
                        break;
                }
            }
        }
        

        window.clear();
        tank.draw(window);
        window.display();
    }

    return 0;
}
