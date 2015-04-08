cmake_minimum_required(VERSION 2.8)

project(isPrimal)

# Require MPI for this project:
find_package(MPI REQUIRED)
set(CMAKE_CXX_COMPILE_FLAGS ${MPI_COMPILE_FLAGS} ${CMAKE_CXX_COMPILE_FLAGS})
set(CMAKE_CXX_LINK_FLAGS ${MPI_LINK_FLAGS} ${CMAKE_CXX_LINK_FLAGS})
include_directories(${MPI_INCLUDE_PATH})
if(UNIX)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")
endif()

#Sciezka ze wszystkimi naglowkami. W razie potrzeb mozna rozbic na osobne foldery.
include_directories ("inc/")

add_library(Master src/master.cpp)
add_library(Slave src/slave.cpp)

add_executable(Main src/main.cpp)

target_link_libraries(Main ${MPI_LIBRARIES} Master Slave)