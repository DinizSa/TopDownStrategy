#include <SFML/Graphics.hpp>

#include <iostream>

#include "Tank.hpp"
#include "PhysicsBody.hpp"


#include "Subject.hpp"
#include "Observer.hpp"

int main()
{
    
    
    int windowWidth = 800;
    int windowHeight = 800;
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Please Tanks");
    
    
    sf::Vector2f size = {200.f, 200.f};
    sf::Vector2f position = {200.f, 200.f};
    Tank tank = Tank(size, position);
    
    sf::Vector2f sizeBody = {120.f, 200.f};
    PhysicsBody body(sizeBody);
    body.translate(position);
    
    sf::Vector2f position2 = {200.f, 410.f};
    PhysicsBody body2(sizeBody);
    body.translate(position2);
    
    Tank tank2 = Tank(size, position2);
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::MouseButtonPressed){
                if (event.mouseButton.button == sf::Mouse::Left) {
                    std::cout << event.mouseButton.x << ", " << event.mouseButton.y << std::endl;
                    sf::Vector2f point = {(float)event.mouseButton.x, (float)event.mouseButton.y};
                    tank.contains(point);
//                    if (body.contains(point)) {
//                        std::cout << "hit A " << std::endl;
//                    }
//                    if (body2.contains(point)) {
//                        std::cout << "hit B " << std::endl;
//                    }
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
                        body.rotate(-5.f);
                        if (body.contains(body2)) {
                            body.rotate(5.f);
                            break;
                        }
                        tank.rotateAntiClock();
                        break;
                    case sf::Keyboard::Scan::D:
                        body.rotate(5.f);
                        if (body.contains(body2)) {
                            body.rotate(-5.f);
                            break;
                        }
                        tank.rotateClock();
                        break;
                    case sf::Keyboard::Scan::S:
                        body.translate(5.f);
                        if (body.contains(body2)) {
                            body.translate(-5.f);
                            break;
                        }
                        tank.moveBack();
                        break;
                    case sf::Keyboard::Scan::W:
                        body.translate(-5.f);
                        if (body.contains(body2)) {
                            body.translate(5.f);
                            break;
                        }
                        tank.moveFront();
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
