cmake_minimum_required(VERSION 2.6)
project(CPUNAIVE)

set(CMAKE_CXX_FLAGS "-std=c++1y -pthread -DDEBUG -DN128")
include_directories(${PROJECT_BINARY_DIR}/include)
include_directories(${CPUNAIVE_SOURCE_DIR}/include)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
add_executable(regression src/Algo.cpp src/Graph.cpp src/keyValueStore.cpp src/regression.cpp src/debug.cpp)

