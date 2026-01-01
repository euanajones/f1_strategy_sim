cmake_minimum_required(VERSION 4.1)
project(f1_strategy_sim)

set(CMAKE_CXX_STANDARD 20)

add_executable(f1_strategy_sim src/main.cpp
        src/Driver.cpp
        src/Driver.hpp
        src/CarState.cpp
        src/CarState.hpp
        src/RaceState.cpp
        src/RaceState.hpp
        src/simulation.hpp
        src/simulation.cpp
)
