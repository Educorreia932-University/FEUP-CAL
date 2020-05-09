
#include "UserInterface/UserInterface.h"
#include <iostream>
#include "GraphFactory.h"

using namespace std;

int main() {
    UserInterface ui;
    //ui.mainMenuSelection(ui.showMainMenu());
    auto *g = new GraphFactory();
    g->readVertex("../../utils/map_extraction/nodes.csv");
    auto graph = new Graph();
    vector<Vertex *> vertexes;
    for (int i = 0; i < 10; ++i) {
        vertexes.push_back(new Vertex(i));
        graph->addVertex(vertexes[i]->getID());
        if (i > 2)
            graph->addEdge(vertexes[i]->getID(),vertexes[i - 3]->getID(), 0);
    }
    graph->floydWarshallShortestPath();
    auto res = graph->getFloydWarshallPath(9, 0);

    for (auto elem : res)
        cout << elem << ' ';
    return 0;
}
