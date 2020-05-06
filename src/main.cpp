
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
        if (i > 2)
            vertexes[i]->addEdge(vertexes[i - 3], 0);
        graph->addVertex(vertexes[i]);
    }
    graph->floydWarshallShortestPath();
    auto res = graph->getFloydWarshallPath(9, 0);
    for (auto elem : res)
        cout << elem << '\n';
    return 0;
}
