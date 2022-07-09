#include <iostream>
#include "Pathfinder.h"

int main() {

    sf::RenderWindow window(sf::VideoMode(800.f, 600.f), "Pathfinder");
    std::vector<sf::RectangleShape> nodes;
    std::vector<sf::RectangleShape> walls;

    Pathfinder::Generator generator;
    sf::Vector2f tiles(25, 25);
    generator.setWorldSize({25, 25});
    generator.setHeuristic(Pathfinder::Heuristic::euclidean);
    generator.setDiagonalMovement(false);
    sf::RectangleShape wall;

    float dimX = (float)window.getSize().x / tiles.x;
    float dimY = (float)window.getSize().y / tiles.y;

    generator.addCollision({3, 3});
    wall.setSize(sf::Vector2f(dimX, dimY));
    wall.setPosition(3*dimX, 3*dimY);
    wall.setFillColor(sf::Color::Green);
    walls.push_back(wall);

    generator.addCollision({10, 20});
    wall.setSize(sf::Vector2f(dimX, dimY));
    wall.setPosition(10*dimX, 20*dimY);
    wall.setFillColor(sf::Color::Green);
    walls.push_back(wall);

    generator.addCollision({4, 5});
    wall.setSize(sf::Vector2f(dimX, dimY));
    wall.setPosition(4*dimX, 5*dimY);
    wall.setFillColor(sf::Color::Green);
    walls.push_back(wall);

    generator.addCollision({5, 4});
    wall.setSize(sf::Vector2f(dimX, dimY));
    wall.setPosition(5*dimX, 4*dimY);
    wall.setFillColor(sf::Color::Green);
    walls.push_back(wall);

    generator.addCollision({10, 10});
    wall.setSize(sf::Vector2f(dimX, dimY));
    wall.setPosition(10*dimX, 10*dimY);
    wall.setFillColor(sf::Color::Green);
    walls.push_back(wall);

    std::cout << "Generate path ... \n";
    auto path = generator.findPath({0, 0}, {10, 9});



    for(auto& coordinate : path) {

        sf::RectangleShape node;
        std::cout << coordinate.x << " " << coordinate.y << "\n";
        node.setSize(sf::Vector2f((float)window.getSize().x/tiles.x, (float)window.getSize().y/tiles.y));
        node.setPosition((float)coordinate.x*dimX, (float)coordinate.y*dimY);
        if(coordinate == path.front() || coordinate == path.back())
            node.setFillColor(sf::Color::Yellow);
        else
            node.setFillColor(sf::Color::Red);
        nodes.push_back(node);

    }

    sf::Event event{};

    while(window.isOpen()){

        while(window.pollEvent(event)){

            if(event.type == sf::Event::Closed)
                window.close();

        }

        window.clear(sf::Color::Cyan);

        for(auto &n : nodes)
            window.draw(n);

        for(auto &w : walls)
            window.draw(w);

        window.display();

    }

    return 0;
}
