#include <SFML/Graphics.hpp>

#include <iostream>

#include "Tank.hpp"

int main()
{
    int windowWidth = 600;
    int windowHeight = 600;
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Please Tanks");
    
    int tankWidth = 200;
    int tankHeight = 200;
    int posX = 300.f;
    int posY = 200.f;
//    float speed = 2.5f;
//    float tracksAngularSpeed = 90.f;
//    float gunAngularSpeed = 45.f;
//
////    Tracks
//    sf::Texture trackTexture;
//    if (!trackTexture.loadFromFile("/Users/Shared/merda/PleaseTanks/images/Track_1_A.png")) {
//        std::cout << "Error \n";
//    }
//    sf::RectangleShape rectTrackA, rectTrackB;
////    rectTrackA.setSize({0.15f * tankWidth, 0.9f * tankHeight});
////    rectTrackA.setTexture(&trackTexture);
////    rectTrackA.setOrigin(tankWidth/2, tankHeight/2);
////    rectTrackA.setPosition(posX + 0.24f * tankWidth, posY + 0.05f * tankHeight);
//
//    float trackW = 0.15f * tankWidth;
//    float trackH = 0.9f * tankHeight;
//    rectTrackB.setSize({trackW, trackH});
//    rectTrackB.setTexture(&trackTexture);
//    rectTrackB.setOrigin(trackW / 2, trackH / 2);
//    rectTrackB.setPosition(posX + tankWidth/4, posY);
//
////    Hull
//    sf::RectangleShape rectHull;
//    rectHull.setSize({200, 200});
//    sf::Texture hullTexture;
//    if (!hullTexture.loadFromFile("/Users/Shared/merda/PleaseTanks/images/Hull_03.png")) {
//        std::cout << "Error \n";
//    }
//    rectHull.setTexture(&hullTexture);
//    rectHull.setOrigin(tankWidth/2, tankHeight/2);
//    rectHull.setPosition(posX, posY);
//
//    //    Gun
//    sf::RectangleShape rectGun;
//    rectGun.setSize({200, 200});
//    sf::Texture gunTexture;
//    if (!gunTexture.loadFromFile("/Users/Shared/merda/PleaseTanks/images/Gun_01.png")) {
//        std::cout << "Error \n";
//    }
//    rectGun.setTexture(&gunTexture);
//    rectGun.setOrigin(tankWidth/2, tankHeight*0.6f);
//    rectGun.setPosition(posX, posY);
//
//
//    sf::Transform tankTransform;
    
    Tank tank = Tank({200.f, 200.f});

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
