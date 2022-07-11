#include <iostream>
#include "Pathfinder.h"

int main() {

    sf::RenderWindow window(sf::VideoMode(800.f, 600.f), "Pathfinder");

    Pathfinder::Generator generator;
    sf::Vector2f tiles(25, 25);

    generator.setWorldSize(tiles);
    generator.setHeuristic(Pathfinder::Heuristic::euclidean);
    generator.setDiagonalMovement(true);

    sf::RectangleShape wall;

    float dimX = (float)window.getSize().x / tiles.x;
    float dimY = (float)window.getSize().y / tiles.y;

    generator.addCollision({3, 3}, sf::Vector2f(dimX, dimY));
    generator.addCollision({10, 20}, sf::Vector2f(dimX, dimY));
    generator.addCollision({4, 5}, sf::Vector2f(dimX, dimY));
    generator.addCollision({5, 4}, sf::Vector2f(dimX, dimY));
    generator.addCollision({10, 10}, sf::Vector2f(dimX, dimY));
    generator.addCollision({2, 3}, sf::Vector2f(dimX, dimY));
    generator.addCollision({20, 10}, sf::Vector2f(dimX, dimY));
    generator.addCollision({4, 15}, sf::Vector2f(dimX, dimY));
    generator.addCollision({15, 4}, sf::Vector2f(dimX, dimY));
    generator.addCollision({3, 2}, sf::Vector2f(dimX, dimY));

    std::cout << "Generate path ... \n";
    auto path = generator.findPath({0, 0}, {10, 9});

    for(auto& coordinate : path) {

        sf::RectangleShape node;
        std::cout << coordinate.x << " " << coordinate.y << "\n";

        if(coordinate == path.front() || coordinate == path.back())
            generator.findSourceTarget(true);
        else
            generator.findSourceTarget(false);

        generator.addNode(coordinate, sf::Vector2f((float)window.getSize().x/tiles.x, (float)window.getSize().y/tiles.y));

    }

    sf::Event event{};

    while(window.isOpen()){

        while(window.pollEvent(event)){

            if(event.type == sf::Event::Closed)
                window.close();

            if(event.key.code == sf::Keyboard::Escape)
                window.close();

        }

        window.clear(sf::Color::Cyan);

        generator.render(&window);

        window.display();

    }

    return 0;
}
