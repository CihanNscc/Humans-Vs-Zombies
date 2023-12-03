cmake_minimum_required(VERSION 3.26)
project(zombies)

set(CMAKE_CXX_STANDARD 17)

add_executable(zombies main.cpp
        GameSpecs.h
        Human.h
        Zombie.h
        City.cpp
        Organism.cpp
        Human.cpp
        Zombie.cpp)
