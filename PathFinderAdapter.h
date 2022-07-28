#ifndef ASTAR_PATHFINDERADAPTER_H
#define ASTAR_PATHFINDERADAPTER_H

#include "Pathfinder.h"
#include <cmath>


class PathFinderAdapter: public Pathfinder::Generator{

public:

    PathFinderAdapter( const std::vector<sf::Vector2i> &walls,sf::Vector2f size, float time, sf::Vector2f source, sf::Vector2f target);

    sf::Vector2f getMovement( sf::Vector2f end, sf::Vector2f currentPosition);

    std::vector<Pathfinder::Vec2i>& getPath(){
        return path;
    }

private:

    sf::Vector2f stepEndPosition;
    sf::Vector2f stepStartPosition;
    int currentIndex;
    sf::Vector2f endPosition;
    std::vector<Pathfinder::Vec2i> path;
    sf::Vector2f currentPosition;



    float updateTime;
    sf::Clock clock;

    void updatePath();
    void updateCurrentTarget();
    static sf::Vector2f tilesToPixels(Pathfinder::Vec2i tilePos);
    static Pathfinder::Vec2i pixelToTiles(sf::Vector2f pixelPos);





};


#endif //ASTAR_PATHFINDERADAPTER_H
