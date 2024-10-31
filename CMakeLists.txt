cmake_minimum_required(VERSION 3.30)
project(main)

set(CMAKE_CXX_STANDARD 17)

add_executable(main 
               src/main.cpp
               src/cube/magicfive.cpp
               src/solver/solver.cpp
               src/hillclimb/hillclimb.cpp
               src/hillclimb/stochastic.cpp
               src/advanced/genetic.cpp
               src/hillclimb/randomrestart.cpp
               src/advanced/simulatedannealing.cpp)