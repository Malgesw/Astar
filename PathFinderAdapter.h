#ifndef ASTAR_PATHFINDERADAPTER_H
#define ASTAR_PATHFINDERADAPTER_H

#include "Pathfinder.h"


class PathFinderAdapter: public Pathfinder::Generator{

public:

    PathFinderAdapter( const std::vector<sf::Vector2i> &walls,sf::Vector2f size, float time);

    sf::Vector2f getMovement( sf::Vector2f end, sf::Vector2f currentPosition);

    std::vector<Pathfinder::Vec2i>& getPath(){
        return path;
    }

private:

    Pathfinder::Vec2i stepEndPosition;
    Pathfinder::Vec2i stepStartPosition;
    int currentIndex;
    sf::Vector2f endPosition;
    std::vector<Pathfinder::Vec2i> path;
    sf::Vector2f currentPosition;



    float updateTime;
    sf::Clock clock;

    void updatePath();
    void updateCurrentTarget();





};


#endif //ASTAR_PATHFINDERADAPTER_H
