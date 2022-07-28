cmake_minimum_required(VERSION 3.21)
project(Astar)

set(CMAKE_CXX_STANDARD 14)

add_executable(Astar main.cpp Pathfinder.cpp Pathfinder.h PathFinderAdapter.cpp PathFinderAdapter.h)


set(SFML_DIR /usr/include/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories(/usr/local/include)
target_link_libraries(Astar sfml-system sfml-window sfml-graphics sfml-audio sfml-network)