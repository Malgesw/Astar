#include <iostream>
#include "Pathfinder.h"
#include "PathFinderAdapter.h"

int main() {



    sf::RenderWindow window(sf::VideoMode(800.f, 600.f), "Pathfinder");
    //window.setFramerateLimit(60);
    sf::Vector2f tiles(25, 25);

    float dimX = (float)window.getSize().x / tiles.x;
    float dimY = (float)window.getSize().y / tiles.y;


    std::vector<sf::Vector2i> walls;

    walls={sf::Vector2i (3,3),sf::Vector2i (10,20),sf::Vector2i (4,5),sf::Vector2i (5,4),sf::Vector2i (10,10),
          sf::Vector2i (2,3),sf::Vector2i (20,10),sf::Vector2i (4,15),sf::Vector2i (15,4),sf::Vector2i (3,2),};

    sf::RectangleShape player(sf::Vector2f(dimX, dimY));
    player.setFillColor(sf::Color::Blue);
    player.setPosition(200.f, 200.f);

    sf::RectangleShape enemy(sf::Vector2f(dimX, dimY));
    enemy.setFillColor(sf::Color::Red);


    PathFinderAdapter finder(walls,sf::Vector2f(dimX, dimY),1.f, sf::Vector2f(0.f, 0.f), sf::Vector2f(200.f/32, 200.f/24));

    Pathfinder::Generator generator;

    finder.setWorldSize(tiles);
    finder.setHeuristic(Pathfinder::Heuristic::manhattan);
    finder.setDiagonalMovement(false);

    sf::RectangleShape wall;




    //sf::RectangleShape target(sf::Vector2f(dimX, dimY));
    //target.setFillColor(sf::Color::Yellow);
    //target.setPosition(600.f, 200.f);


/*
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
    */




    /*std::cout << "Generate path ... \n";
    //auto path = generator.findPath({0, 0}, {10, 9});
    auto path = generator.findPath({(int)enemy.getPosition().x/25, (int)enemy.getPosition().y/25},
                                   {(int)target.getPosition().x/25, (int)target.getPosition().y/25});

    std::reverse(path.begin(), path.end());
    std::cout << (int)target.getPosition().x/25 << " " << (int)target.getPosition().y/25 <<std::endl;


    for(auto& coordinate : path) {

        std::cout << coordinate.x << " " << coordinate.y << "\n";

        if(coordinate == path.front() || coordinate == path.back())
            generator.findSourceTarget(true);
        else
            generator.findSourceTarget(false);

        generator.addNode(coordinate, sf::Vector2f((float)window.getSize().x/tiles.x, (float)window.getSize().y/tiles.y));

    }
     */

    sf::Event event{};
    float dt;
    sf::Clock clock;

    while(window.isOpen()){

        dt = clock.getElapsedTime().asSeconds();
        clock.restart();

        while(window.pollEvent(event)){

            if(event.type == sf::Event::Closed)
                window.close();

            if(event.key.code == sf::Keyboard::Escape)
                window.close();

        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::J))
            player.move(-100.5f*dt, 0.f);

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::L))
            player.move(100.5f*dt, 0.f);

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::I))
            player.move(0.f, -100.5f*dt);

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::K))
            player.move(0.f, 100.5f*dt);

        sf::Vector2f movement;

        //if(std::abs(player.getPosition().x-enemy.getPosition().x)<200||std::abs(player.getPosition().y-enemy.getPosition().y)<200){


        movement=finder.getMovement(player.getPosition(),enemy.getPosition());

        //if(enemy.getGlobalBounds().intersects(player.getGlobalBounds()))
        // movement = sf::Vector2f(0.f, 0.f);

        double norm = sqrt(pow(enemy.getPosition().x - player.getPosition().x, 2) + pow(enemy.getPosition().x - player.getPosition().x, 2));
        if(norm < 400.f)
            enemy.move(movement*dt);

           /* for(auto &p : path) {

                movement.x = std::abs(enemy.getPosition().x/25 - p.x) * dimX;
                movement.y = std::abs(enemy.getPosition().y/25 - p.y) * dimY;

                enemy.move(movement);

                //enemy.setPosition(p.x*25, p.y*25);

                //if(enemy.getPosition().x > target.getPosition().x && enemy.getPosition().y > target.getPosition().y)
                    //enemy.setPosition(target.getPosition());

            }
        */

        //}
        std::vector<Pathfinder::Vec2i> path;
        std::vector<sf::RectangleShape> drawablePath;
        path=finder.getPath();

        for (auto &step : path){
            sf::RectangleShape shape;
            shape.setSize(sf::Vector2f(dimX, dimY));
            shape.setFillColor(sf::Color::White);
            shape.setPosition((float)step.x*32, (float)step.y*24);
            drawablePath.push_back(shape);
        }

        //if(enemy.getGlobalBounds().intersects(player.getGlobalBounds())) {
            //std::cout << "You've taken damage!" << std::endl;
        //}



        window.clear(sf::Color::Cyan);

        //generator.render(&window);
        finder.render(&window);
        //window.draw(target);
        for(auto &s : drawablePath)
            window.draw(s);
        window.draw(player);
        window.draw(enemy);



        window.display();


    }

    return 0;
}
