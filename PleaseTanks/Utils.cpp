//
//  Utils.cpp
//  PleaseTanks
//
//  Created by Diniz Sá on 17/09/2023.
//

#include "Utils.hpp"
#include <cmath>

float Utils::getDistance(const sf::Vector2f& a, const sf::Vector2f& b) {
    return getLength(b.x - a.x, b.y - a.y);
}
float Utils::getLength(float x, float y) {
    return sqrt(pow(x, 2) + pow(y, 2));
}
float Utils::getLength(const sf::Vector2f& v) {
    return sqrt(pow(v.x, 2) + pow(v.y, 2));
}
float Utils::getAngle(const sf::Vector2f& v) {
    float length = Utils::getLength(v);
    auto ang = (acos(v.x / length)) * 180 / M_PI;
    bool firstSecondQuadrant = v.y >= 0.f;
    return firstSecondQuadrant ? ang : -ang;
}
sf::Vector2f Utils::getVector(float rotationDegrees, float hypotenusa) {
    float rotRadians = Utils::getRadians(rotationDegrees);
    return sf::Vector2f({hypotenusa * sin(rotRadians), -hypotenusa * cos(rotRadians)});
}

float Utils::getDegrees(float radians) {
    return radians * 180 / M_PI;
}
float Utils::getRadians(float degrees) {
    return degrees * M_PI / 180;
}

struct Node {
    sf::Vector2f center;
    float radius;
    float aCost, bCost, abCost;
    sf::Vector2f parent;
    bool isOriginal = false;
};

std::vector<Node> removeNode(std::vector<Node>& nodes, const Node& node) {
    for (auto it = nodes.begin(); it != nodes.end();) {
        bool isSame = Utils::getDistance((*it).center, node.center) < 0.01f;
        if (isSame) {
            nodes.erase(it);
        } else {
            it++;
        }
    }
    return nodes;
}
bool contains(const std::vector<Node>& nodes, const Node& node) {
    for (auto& n : nodes) {
        bool isSame = Utils::getDistance(n.center, node.center) < 0.01f;
        if (isSame)
            return true;
    }
    return false;
}
Node* getNode(std::vector<Node>& nodes, const Node& node) {
    for (auto& n : nodes) {
        bool isSame = Utils::getDistance(n.center, node.center) < 0.01f;
        if (isSame)
            return &n;
    }
    return nullptr;
}
std::vector<sf::Vector2f> getPoints(const std::vector<Node>& nodes, const Node& finalNode, const sf::Vector2f& destination) {
    std::vector<sf::Vector2f> points;
    points.reserve(nodes.size() + 2);
    points.push_back(destination);
    points.push_back(finalNode.center);
    Node node = finalNode;
    while (!node.isOriginal) {
        sf::Vector2f parent = node.parent;
        for (auto& n : nodes) {
            bool isSame = Utils::getDistance(n.center, parent) < 0.01f;
            if (isSame) {
                points.emplace_back(n.center);
                node = n;
                break;
            }
        }
    }
    points.pop_back();
    
    std::vector<sf::Vector2f> medianPointsRange;
    medianPointsRange.reserve(points.size());
    medianPointsRange.push_back(destination);
    int delta = 2;
    for (int i = 0; i < points.size(); i++) {
        int counter = 0;
        sf::Vector2f sum;
        for (int j = -delta; j <= delta; j++) {
            int index = i + j;
            if (index < 0 || index > points.size() - 1)
                continue;
            sum += points[index];
            counter++;
        }
        sf::Vector2f medianPoint = sum / (float)counter;
        medianPointsRange.push_back(medianPoint);
    }
    return medianPointsRange;
}
Node getLowerCostNode(const std::vector<Node>& nodes) {
    Node cheaper = nodes[0];
    for (auto& node: nodes) {
        if (node.abCost < cheaper.abCost) {
            cheaper = node;
        } else if (node.abCost == cheaper.abCost) {
            if (node.bCost < cheaper.bCost) {
                cheaper = node;
            }
        }
    }
    return cheaper;
}

std::vector<sf::Vector2f> Utils::getPathPoints(PhysicsBody* walker, sf::Vector2f destination) {
    std::vector<sf::Vector2f> points;
    points.reserve(100);

    std::vector<Node> open;
    int walkerCollisionMaskId = walker->getCollisionMaskId();
    sf::Vector2f walkerSize = walker->getSize();
    Node firstNode;
    firstNode.center = walker->getCenter();
    firstNode.radius = walker->getRadius();
    firstNode.aCost = 0.f;
    firstNode.bCost = getDistance(firstNode.center, destination);
    firstNode.abCost = firstNode.aCost + firstNode.bCost;
    firstNode.isOriginal = true;
    
    open.push_back(firstNode);
    std::vector<Node> closed;
    closed.reserve(100);
    float minimumDistance = firstNode.radius / 2.f;
    
    auto getNeighbours = [&](Node& node){
        std::vector<Node> neighbours;
        neighbours.reserve(8);
        for (int x = -1; x < 2; x++) {
            for (int y = -1; y < 2; y++) {
                if (x == 0 && y == 0)
                    continue;
                Node neightboor;
                neightboor.radius = firstNode.radius;
                float dx = walkerSize.x / 5.f;
                float dy = walkerSize.y / 5.f;
                neightboor.center = node.center + sf::Vector2f({x * dx, y * dy});
                neightboor.aCost = getDistance(neightboor.center, node.center) + node.aCost;
                neightboor.bCost = getDistance(neightboor.center, destination);
                neightboor.abCost = neightboor.aCost + neightboor.bCost;
                
//              outside window bounds
                if (neightboor.center.x < 0.f || neightboor.center.x > 1200.f)
                    continue;
                if (neightboor.center.y < 0.f || neightboor.center.y > 800.f)
                    continue;

//              included in closed
                if (contains(closed, neightboor))
                    continue;
                
//              if collided with an existing body
                bool collides = false;
                for (auto physicsBody : PhysicsBody::allBodies) {
                    int bodyCollisionMaskId = physicsBody->getCollisionMaskId();
                    if (walkerCollisionMaskId != 0 && bodyCollisionMaskId == walkerCollisionMaskId)
                        continue;
                    if (!physicsBody->getMovementCollisions())
                        continue;
                    auto bodyCenter = physicsBody->getCenter();
                    float distance = getDistance(bodyCenter, neightboor.center);
                    float radiusOther = physicsBody->getRadius();
                    if (distance < neightboor.radius + radiusOther) {
                        collides = true;
                        break;
                    }
                }
                if (!collides) {
                    neighbours.push_back(neightboor);
                }
            }
        }
        return neighbours;
    };
    
    while (true) {
        Node current = getLowerCostNode(open);
        open = removeNode(open, current);
        closed.push_back(current);
        
        float distance = getDistance(current.center, destination);
        if (distance < minimumDistance) {
            points.push_back(current.center);
            points = getPoints(closed, current, destination);
            return points;
        }
        
        std::vector<Node> neighboors = getNeighbours(current);
        for (auto& neighboor : neighboors) {
            Node* exitingNode = getNode(open, neighboor);
            if (exitingNode == nullptr || (neighboor.abCost < exitingNode->abCost)) {
                neighboor.parent = current.center;
                if (exitingNode == nullptr) {
                    open.push_back(neighboor);
                } else {
                    *exitingNode = neighboor;
                }
            }
            
        }
    }
    
    
    return points;
};
