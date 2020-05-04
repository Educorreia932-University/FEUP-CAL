cmake_minimum_required(VERSION 3.16)
project(src)

set(CMAKE_CXX_STANDARD 14)

# The line below is necessary if you are under Windows only
# Comment the line below if you are under Linux or Mac OS
link_libraries(ws2_32 wsock32)

include_directories(.)
include_directories(../lib)
include_directories(UserInterface)

add_executable(src
        UserInterface/UserInterface.cpp
        UserInterface/UserInterface.h
        Graph/Edge.cpp
        Graph/Edge.h
        Graph/Graph.cpp
        Graph/Graph.h
        Graph/GraphFactory.cpp
        Graph/GraphFactory.h
        main.cpp
        Utils.cpp
        Utils.h
        Graph/Vertex.cpp
        Graph/Vertex.h
        ../lib/connection.cpp
        ../lib/graphviewer.cpp)
