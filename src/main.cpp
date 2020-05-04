
#include "UserInterface/UserInterface.h"
#include <iostream>
#include "Graph/GraphFactory.h"
#include "../lib/graphviewer.h"

using namespace std;

int main() {
    GraphFactory graphFactory;

    graphFactory.readEdges(R"(C:\Users\skelo\OneDrive\Universidade\2 ano\2 Semestre\Concecao e Analise de Algoritmos\TourMateApp\data\edges.csv)");
    graphFactory.readVertex(R"(C:\Users\skelo\OneDrive\Universidade\2 ano\2 Semestre\Concecao e Analise de Algoritmos\TourMateApp\data\nodes.csv)");

    Graph graph = graphFactory.graph;

//    UserInterface ui;
//    ui.mainMenuSelection(ui.showMainMenu());

    auto gv = new GraphViewer(600, 600, false);
    gv->createWindow(600, 600);

    getchar();

    return 0;
}
