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
    
    sf::Vector2f position2 = {200.f, 410.f};
    Tank tank2 = Tank(size, position2);
    
    
    sf::RectangleShape rect;
    sf::Texture texture;
    rect.setSize({42.f, 246.f});
    texture.loadFromFile("/Users/Shared/merda/PleaseTanks/images/tracksSprites.png");
    rect.setTexture(&texture);
    sf::Rect<int> r;
    r.width = 42;
    r.height = 246;
    r.left = 0;
    r.top = 0;
    rect.setTextureRect(r);
    
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
                        r.left = 42;
                        rect.setTextureRect(r);
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
        tank2.draw(window);
//        window.draw(rect);
        window.display();
    }

    return 0;
}
