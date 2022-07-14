#include <iostream>
#include "Pathfinder.h"

using namespace std::placeholders;

bool Pathfinder::Vec2i::operator == (const Vec2i& coordinates) const
{
    return (x == coordinates.x && y == coordinates.y);
}


Pathfinder::Vec2i operator + (const Pathfinder::Vec2i& left, const Pathfinder::Vec2i& right)
{
    return{ left.x + right.x, left.y + right.y };
}

Pathfinder::Node::Node(Vec2i coordinates, Node *parent)
{
    this->parent = parent;
    this->coordinates = coordinates;
    G = H = 0;
}

unsigned int Pathfinder::Node::getScore() const
{
    return G + H;
}

Pathfinder::Generator::Generator()
{

    setDiagonalMovement(false);
    setHeuristic(&Heuristic::manhattan);

    direction = {
            { 0, 1 }, { 1, 0 }, { 0, -1 }, { -1, 0 },
            { -1, -1 }, { 1, 1 }, { -1, 1 }, { 1, -1 }
    };

    found = false;
    worldSize = {1, 1};
    directions = 4;
}

void Pathfinder::Generator::setWorldSize(sf::Vector2f size)
{
    worldSize = size;

}

void Pathfinder::Generator::setDiagonalMovement(bool enable)
{
    directions = (enable ? 8 : 4);
}

void Pathfinder::Generator::setHeuristic(const HeuristicFunction &heur)
{
    heuristic = std::bind(heur, _1, _2);
}

void Pathfinder::Generator::addCollision(Vec2i coordinates, sf::Vector2f size)
{
    walls.push_back(coordinates);
    sf::RectangleShape shape;
    shape.setFillColor(sf::Color::Green);
    shape.setSize(size);
    shape.setPosition(sf::Vector2f(size.x*(float)coordinates.x, size.y*(float)coordinates.y));
    collisionTiles.push_back(shape);
}

void Pathfinder::Generator::addNode(Pathfinder::Vec2i coordinates, sf::Vector2f size) {

    sf::RectangleShape node;
    node.setSize(size);
    node.setPosition(sf::Vector2f((float)coordinates.x*size.x, (float)coordinates.y*size.y));

    if(found)
        node.setFillColor(sf::Color::Yellow);
    else
        node.setFillColor(sf::Color::Red);

    nodes.push_back(node);

}

void Pathfinder::Generator::removeCollision(Vec2i coordinates)
{
    auto it = std::find(walls.begin(), walls.end(), coordinates);
    if (it != walls.end()) {
        walls.erase(it);
    }
}

void Pathfinder::Generator::clearCollisions()
{
    walls.clear();
}

Pathfinder::CoordinateList Pathfinder::Generator::findPath(Vec2i source, Vec2i target)
{
    Node *current = nullptr;
    NodeSet openSet, closedSet;
    openSet.reserve(100);
    closedSet.reserve(100);
    openSet.push_back(new Node(source));

    while (!openSet.empty()) {
        auto current_it = openSet.begin();
        current = *current_it;

        for (auto it = openSet.begin(); it != openSet.end(); it++) {
            auto node = *it;
            if (node->getScore() <= current->getScore()) {
                current = node;
                current_it = it;
            }
        }

        if (current->coordinates == target) {
            break;
        }

        closedSet.push_back(current);
        openSet.erase(current_it);

        for (unsigned int i = 0; i < directions; ++i) {
            Vec2i newCoordinates(current->coordinates + direction[i]);
            if (detectCollision(newCoordinates) ||
                findNodeOnList(closedSet, newCoordinates)) {
                continue;
            }

            unsigned int totalCost = current->G + ((i < 4) ? 10 : 14);

            Node *successor = findNodeOnList(openSet, newCoordinates);
            if (successor == nullptr) {
                successor = new Node(newCoordinates, current);
                successor->G = totalCost;
                successor->H = heuristic(successor->coordinates, target);
                openSet.push_back(successor);
            }
            else if (totalCost < successor->G) {
                successor->parent = current;
                successor->G = totalCost;
            }
        }
    }

    CoordinateList path;
    while (current != nullptr) {
        path.push_back(current->coordinates);
        current = current->parent;
    }

    releaseNodes(openSet);
    releaseNodes(closedSet);

    return path;
}

Pathfinder::Node* Pathfinder::Generator::findNodeOnList(NodeSet& nodeSet, Vec2i coordinates)
{
    for (auto node : nodeSet) {
        if (node->coordinates == coordinates) {
            return node;
        }
    }
    return nullptr;
}

void Pathfinder::Generator::releaseNodes(NodeSet& nodeSet)
{
    for (auto it = nodeSet.begin(); it != nodeSet.end();) {
        delete *it;
        it = nodeSet.erase(it);
    }
}

bool Pathfinder::Generator::detectCollision(Vec2i coordinates)
{
    if (coordinates.x < 0 || coordinates.x >= worldSize.x ||
        coordinates.y < 0 || coordinates.y >= worldSize.y ||
        std::find(walls.begin(), walls.end(), coordinates) != walls.end()) {
        return true;
    }
    return false;
}

void Pathfinder::Generator::render(sf::RenderTarget *target) {

    for(auto &c : collisionTiles) {
        target->draw(c);
    }


    for(auto &n : nodes) {
        n.setFillColor(sf::Color::White);
        target->draw(n);

    }

}

void Pathfinder::Generator::findSourceTarget(bool isFound) {

   if(isFound){
       found = true;
   }
   else
       found = false;

}

Pathfinder::Vec2i Pathfinder::Heuristic::getDelta(Vec2i source, Vec2i target)
{
    return{ abs(source.x - target.x),  abs(source.y - target.y) };
}

unsigned int Pathfinder::Heuristic::manhattan(Vec2i source, Vec2i target)
{
    auto delta = getDelta(source, target);
    return static_cast<unsigned int>(10 * (delta.x + delta.y));
}

unsigned int Pathfinder::Heuristic::euclidean(Vec2i source, Vec2i target)
{
    auto delta = getDelta(source, target);
    return static_cast<unsigned int>(10 * sqrt(pow(delta.x, 2) + pow(delta.y, 2)));
}

unsigned int Pathfinder::Heuristic::octagonal(Vec2i source, Vec2i target)
{
    auto delta = getDelta(source, target);
    return 10 * (delta.x + delta.y) + (-6) * std::min(delta.x, delta.y);
}

