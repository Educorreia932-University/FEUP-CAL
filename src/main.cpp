
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

    auto gv = new GraphViewer(900, 900, false);
    gv->setBackground("../data/map.png");
    gv->createWindow(900, 900);

    double min_lon = -8.6226691;
    double max_lon = -8.5989075;
    double min_lat = 41.1584432;
    double max_lat = 41.14049;

    gv->defineEdgeCurved(false);

    for (Vertex* v : graph.getVertexSet()) {
        gv->addNode(
                v->getID(),
                (v->lon - min_lon) / (max_lon - min_lon) * 900,
                (v->lat - min_lat) / (max_lat - min_lat) * 900
        );

        gv->setVertexSize(v->getID(), 10);
    }

    int edge_id = 0;

    for (Vertex* v : graph.getVertexSet())
        for (const Edge& w : v->getAdj()) {
            gv->addEdge(edge_id, v->getID(), w.getDest()->getID(), EdgeType::UNDIRECTED);
            edge_id++;
        }

    gv->rearrange();
    getchar();

    return 0;
}
