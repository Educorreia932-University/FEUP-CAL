cmake_minimum_required(VERSION 3.15)
project(TourMateApp)

set(CMAKE_CXX_STANDARD 20)

add_executable(TourMateApp main.cpp Node.cpp Node.h Category.cpp Category.h POI.cpp POI.h Street.cpp Street.h Edge.cpp Edge.h
        CsvReader.cpp CsvReader.h Graph.h Graph.cpp)