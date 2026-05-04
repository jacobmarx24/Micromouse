cmake_minimum_required(VERSION 4.1)
project(Micromouse)

set(CMAKE_CXX_STANDARD 11)
include_directories(/opt/homebrew/include/)
link_directories(/opt/homebrew/lib)


add_executable(Micromouse source/main.cpp
        source/RaceCarDriver.h
        source/constants.h
        source/Racer.h
        source/timer.h
        source/DisjointSet.h
        source/SDL_Plotter.cpp
        source/SDL_Plotter.h)

target_link_libraries(${PROJECT_NAME} SDL2 SDL2_mixer)
