cmake_minimum_required(VERSION 3.15)
project(src)

set(CMAKE_CXX_STANDARD 14)

# The line below is necessary if you are under Windows only
# Comment the line below if you are under Linux or Mac OS
if (WIN32)
    link_libraries(ws2_32 wsock32)
endif ()

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
        Graph/FloydStorage.cpp
        Graph/FloydStorage.h
        Graph/PoiStorage.cpp
        Graph/PoiStorage.h
        ../lib/connection.cpp
        ../lib/graphviewer.cpp)
