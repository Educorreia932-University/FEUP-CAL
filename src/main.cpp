
#include "UserInterface/UserInterface.h"
#include "Graph/GraphFactory.h"
#include "Storage/PoiStorage.h"

using namespace std;


int main() {
    /*<Creating graph*/
    GraphFactory graphFactory;

    graphFactory.readVertex("../data/nodes_PORTO.csv");
    graphFactory.readEdges("../data/edges_PORTO.csv");

    Graph graph = graphFactory.graph;

    /*<Reading the POIS*/
    auto* poiStorage = new PoiStorage("PORTO");

    if (!poiStorage->readPois()){
        ERRORS("Not possible to read POIS");
        exit(1);
    }

    /*<initiating the interface*/
    UserInterface ui(&graph, poiStorage);
    ui.mainMenuSelection();


    return 0;
}
