cmake_minimum_required(VERSION 2.6)
project(CPUNAIVE)

set(CMAKE_CXX_FLAGS "-std=c++1y -g -pthread -DDEBUG -DN1024 -DUNORDERED ")
include_directories(${CPUNAIVE_SOURCE_DIR}/include)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

add_executable(regression 
                src/regression.cpp 
                src/Graph.cpp 
                src/keyValueStore.cpp 
                src/debug.cpp 
                src/AlgoRandomAnt.cpp 
                src/AlgoAnt.cpp 
                src/AlgoAnt2.cpp 
                src/AlgoAntSystem.cpp
                src/AlgoAntSystem2.cpp
                src/AlgoAntSysmte3.cpp
                )

add_executable(regression2 
                src/regression2.cpp 
                src/Graph.cpp 
                src/keyValueStore.cpp 
                src/debug.cpp 
                src/AlgoRandomAnt.cpp 
                src/AlgoAnt.cpp 
                src/AlgoAnt2.cpp 
                src/AlgoAntSystem.cpp
                src/AlgoAntSystem2.cpp
                src/AlgoAntSystem3.cpp
                )

add_executable(regression3 
                src/regression3.cpp 
                src/Graph.cpp 
                src/keyValueStore.cpp 
                src/debug.cpp 
                src/AlgoRandomAnt.cpp 
                src/AlgoAnt.cpp 
                src/AlgoAnt2.cpp 
                src/AlgoAntSystem.cpp
                src/AlgoAntSystem2.cpp
                src/AlgoAntSystem3.cpp
                )

