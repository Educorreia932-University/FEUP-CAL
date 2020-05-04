
#include "UserInterface/UserInterface.h"
#include <iostream>
#include "Graph/GraphFactory.h"
#include "../lib/graphviewer.h"

using namespace std;

int main() {
    GraphFactory graphFactory;

    graphFactory.readVertex(R"(C:\Users\skelo\OneDrive\Universidade\2 ano\2 Semestre\Concecao e Analise de Algoritmos\TourMateApp\data\nodes.csv)");
    graphFactory.readEdges(R"(C:\Users\skelo\OneDrive\Universidade\2 ano\2 Semestre\Concecao e Analise de Algoritmos\TourMateApp\data\edges.csv)");

    Graph graph = graphFactory.graph;

//    UserInterface ui;
//    ui.mainMenuSelection(ui.showMainMenu());

    auto gv = new GraphViewer(1920, 1080, true);
    gv->createWindow(1920, 1080);

    for (Vertex* v : graph.getVertexSet())
        gv->addNode(v->getID());

    int edge_id = 0;

    for (Vertex* v : graph.getVertexSet())
        for (const Edge& w : v->getAdj()) {
            gv->addEdge(edge_id, v->getID(), w.getDest()->getID(), EdgeType::DIRECTED);
            edge_id++;
        }

    gv->rearrange();
    getchar();

    return 0;
}
