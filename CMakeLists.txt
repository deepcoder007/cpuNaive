cmake_minimum_required(VERSION 2.6)
project(CPUNAIVE)

set(CMAKE_CXX_FLAGS "-std=c++1y -g -pthread -DDEBUG -DN1024")
include_directories(${PROJECT_BINARY_DIR}/include)
include_directories(${CPUNAIVE_SOURCE_DIR}/include)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
add_executable(regression2 
                src/Graph.cpp 
                src/keyValueStore.cpp 
                src/regression.cpp 
                src/debug.cpp 
                src/AlgoRandomAnt.cpp 
                src/AlgoAnt.cpp 
                src/AlgoAnt2.cpp 
                src/AlgoAntSystem.cpp
                src/AlgoAntSystem2.cpp)

