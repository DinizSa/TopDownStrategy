#include <SFML/Graphics.hpp>

#include <iostream>

#include "Tank.hpp"
#include "PhysicsBody.hpp"

int main()
{
    int windowWidth = 600;
    int windowHeight = 600;
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Please Tanks");
    
    
    sf::Vector2<float> size = {200.f, 200.f};
    sf::Vector2<float> position = {200.f, 200.f};
    Tank tank = Tank(size, position);
    
    sf::Vector2<float> sizeBody = {120.f, 200.f};
    PhysicsBody body(sizeBody, position, {0.f, 0.f});
    
    sf::Vector2<float> position2 = {200.f, 410.f};
    PhysicsBody body2(sizeBody, position2, {0.f, 0.f});
    
    Tank tank2 = Tank(size, position2);
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::MouseButtonPressed){
                if (event.mouseButton.button == sf::Mouse::Left) {
                    std::cout << event.mouseButton.x << ", " << event.mouseButton.y << std::endl;
                    sf::Vector2<float> point = {(float)event.mouseButton.x, (float)event.mouseButton.y};
                    if (body.contains(point)) {
                        std::cout << "hit A " << std::endl;
                    }
                    if (body2.contains(point)) {
                        std::cout << "hit B " << std::endl;
                    }
                }
            }
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
                        body.rotate(-5.f);
                        break;
                    case sf::Keyboard::Scan::D:
                        tank.rotateClock();
                        body.rotate(5.f);
                        break;
                    case sf::Keyboard::Scan::S:
                        tank.moveBack();
                        body.translate(5.f);
                        std::cout << "contains: " << (body.contains(body2) ? "true" : "false") << std::endl;
//                        std::cout << "contains: " << ((body.contains(body2) || body2.contains(body)) ? "true" : "false") << std::endl;
                        break;
                    case sf::Keyboard::Scan::W:
                        tank.moveFront();
                        body.translate(-5.f);
                        std::cout << "contains: " << (body.contains(body2) ? "true" : "false") << std::endl;
                        break;
                    default:
                        break;
                }
            }
        }
        

        window.clear();
        tank.draw(window);
        tank2.draw(window);
        window.display();
    }

    return 0;
}
