cmake_minimum_required(VERSION 3.15)
project(TourMateApp)

set(CMAKE_CXX_STANDARD 20)

add_executable(TourMateApp main.cpp Edge.h Vertex.h Graph.h Graph.cpp Vertex.cpp Edge.cpp UserInterface/UserInterface.cpp UserInterface/UserInterface.h)