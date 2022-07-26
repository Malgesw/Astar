#include <iostream>
#include "PathFinderAdapter.h"

PathFinderAdapter::PathFinderAdapter( const std::vector<sf::Vector2i>& walls,sf::Vector2f size, float time):updateTime(time),currentIndex(0) {


    for(auto &w:walls){

        addCollision({w.x,w.y},size);
        clock.restart();
    }
    updatePath();
}



sf::Vector2f PathFinderAdapter::getMovement(sf::Vector2f end, sf::Vector2f position){

    endPosition=sf::Vector2f (end.x/25,end.y/25);
    currentPosition=sf::Vector2f (position.x/25,position.y/25);

    if(clock.getElapsedTime().asSeconds()>updateTime){

        //std::cout<<"clock restarted"<<std::endl;

        updatePath();
        clock.restart();
    }
    stepEndPosition=path[currentIndex];
    sf::Vector2f movement;
    //std::cout<<"target is "<<stepEndPosition.x<<"  "<<stepEndPosition.y<<std::endl;
    //std::cout<<"position is " <<currentPosition.x<<"  "<<currentPosition.y<<std::endl;
    movement.x= ((float)stepEndPosition.x - currentPosition.x) * 32 * 2;
    movement.y= ((float)stepEndPosition.y - currentPosition.y) * 24 * 2;
    //std::cout<<"movement is " <<movement.x<<"  "<<movement.y<<std::endl;
    if(movement.x<32.f && movement.y<24.f) {
        updateCurrentTarget();
    }
    if (movement.x<500.f && movement.y <500.f) {
        return movement;
    }
    else
        return sf::Vector2f (0,0);
}


void PathFinderAdapter::updatePath(){


    //std::cout<<"current position is "<<currentPosition.x<<"   "<<currentPosition.y<<std::endl;
    //std::cout<<"end position is "<<endPosition.x<<"   "<<endPosition.y<<std::endl;

    path= findPath({static_cast<int>(currentPosition.x), static_cast<int>(currentPosition.y)},{static_cast<int>(endPosition.x),
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

