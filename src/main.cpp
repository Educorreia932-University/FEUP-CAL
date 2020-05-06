
#include "UserInterface/UserInterface.h"
#include "Graph/GraphFactory.h"

using namespace std;

int main() {
    GraphFactory graphFactory;

    graphFactory.readVertex(R"(C:\Users\skelo\OneDrive\Universidade\2 ano\2 Semestre\Concecao e Analise de Algoritmos\TourMateApp\data\nodes.csv)");
    graphFactory.readEdges(R"(C:\Users\skelo\OneDrive\Universidade\2 ano\2 Semestre\Concecao e Analise de Algoritmos\TourMateApp\data\edges.csv)");

    Graph graph = graphFactory.graph;

    UserInterface ui(&graph);
    ui.mainMenuSelection(ui.showMainMenu());

    return 0;
}
