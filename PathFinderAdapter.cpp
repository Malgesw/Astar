#include <iostream>
#include "PathFinderAdapter.h"

PathFinderAdapter::PathFinderAdapter( const std::vector<sf::Vector2i>& walls,sf::Vector2f size, float time, sf::Vector2f source, sf::Vector2f target) :
updateTime(time),currentIndex(0), endPosition(target), currentPosition(source) {


    for(auto &w:walls){

        addCollision({w.x,w.y},size);
        clock.restart();
    }
    updatePath();
}



sf::Vector2f PathFinderAdapter::getMovement(sf::Vector2f end, sf::Vector2f position){

    endPosition=sf::Vector2f (end.x/32,end.y/24);
    currentPosition=sf::Vector2f (position.x/32,position.y/24);

    if(clock.getElapsedTime().asSeconds()>updateTime){

        //std::cout<<"clock restarted"<<std::endl;

        updatePath();
        clock.restart();
    }
    sf::Vector2f movement;
    //std::cout<<"target is "<<stepEndPosition.x<<"  "<<stepEndPosition.y<<std::endl;
    //std::cout<<"position is " <<currentPosition.x<<"  "<<currentPosition.y<<std::endl;
    movement.x= ((float)stepEndPosition.x - (float)stepStartPosition.x) * 32;
    movement.y= ((float)stepEndPosition.y - (float)stepStartPosition.y) * 24;
    //std::cout<<"movement is " <<movement.x<<"  "<<movement.y<<std::endl;
    if(std::abs(currentPosition.x - (float)stepEndPosition.x) < 0.01f && std::abs(currentPosition.y - (float)stepEndPosition.y) < 0.01f) {
        updateCurrentTarget();
        stepEndPosition=path[currentIndex];
        stepStartPosition = path[currentIndex-1];
        std::cout << "StepStartPosition : " << stepStartPosition.x << ", " << stepStartPosition.y << std::endl;
        std::cout << "StepEndPosition : " << stepEndPosition.x << ", " << stepEndPosition.y << std::endl;
    }
    if (movement.x<500.f && movement.y <500.f) {
        return movement;
    }
    else
        return {0,0};
}


void PathFinderAdapter::updatePath(){


    //std::cout<<"current position is "<<currentPosition.x<<"   "<<currentPosition.y<<std::endl;
    //std::cout<<"end position is "<<endPosition.x<<"   "<<endPosition.y<<std::endl;

    path = findPath({static_cast<int>(currentPosition.x), static_cast<int>(currentPosition.y)},{static_cast<int>(endPosition.x),
                                                                                           static_cast<int>(endPosition.y)});
    std::reverse(path.begin(),path.end());

    stepStartPosition=path[0];
    stepEndPosition=path[1];
    currentIndex=1;

}

void PathFinderAdapter::updateCurrentTarget(){


    std::cout<<"current index is  "<<currentIndex<<std::endl;
    if(currentIndex<path.size()) {
        currentIndex++;
    }
    else {
        updatePath();
    }

}

