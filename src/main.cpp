
#include "UserInterface/UserInterface.h"
#include <iostream>
#include "Graph/GraphFactory.h"
#include "../lib/graphviewer.h"

using namespace std;

void printTest(vector<ulli> res);
void test1_floyd();
void test2_floyd();
void test1_trajectoryOrder();

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

    for (Capsule c : graph.getVertexSet()) {
        Vertex* v = c.getVertex();

        gv->addNode(
                v->getID(),
                (v->lon - min_lon) / (max_lon - min_lon) * 900,
                (v->lat - min_lat) / (max_lat - min_lat) * 900
        );

        gv->setVertexSize(v->getID(), 10);
    }

    int edge_id = 0;

    for (Capsule c : graph.getVertexSet()) {
        Vertex* v = c.getVertex();

        for (const Edge& w : v->getAdj()) {
            gv->addEdge(edge_id, v->getID(), w.getDest()->getID(), EdgeType::UNDIRECTED);
            edge_id++;
        }
    }

    gv->rearrange();
    getchar();

    //test the floyd warshall greedy aproach 
    test1_trajectoryOrder(); 

    return 0;
}

//TESTS ----------------------------------------------------------------------------

//floyd warshall test1
void test1_floyd(){

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

    printTest(res);
}

//test floydWarshall 2
void test2_floyd(){
    vector<ulli> v = {1,2,3,4,5,6};
    auto graph = new Graph();

    for (int i = 1 ; i < 7; i++ ) graph->addVertex(i);
    graph->addEdge(1,2,1);
    graph->addEdge(1,3,3);
    graph->addEdge(2,3,1);
    graph->addEdge(2,4,5);
    graph->addEdge(2,5,2);
    graph->addEdge(3,5,4);
    graph->addEdge(4,6,1);
    graph->addEdge(4,5,1);
    graph->addEdge(5,4,1);
    graph->addEdge(5,6,4);

    graph->floydWarshallShortestPath();
    auto res = graph->getFloydWarshallPath(1,6);

    printTest(res);

}

//test floydWarshall 2
void test1_trajectoryOrder(){
    vector<ulli> v = {1,2,3,4,5,6};
    auto graph = new Graph();

    for (int i = 1 ; i < 7; i++ ) graph->addVertex(i);
    graph->addEdge(1,2,1);
    graph->addEdge(1,3,3);
    graph->addEdge(2,3,1);
    graph->addEdge(2,4,5);
    graph->addEdge(2,5,2);
    graph->addEdge(3,5,4);
    graph->addEdge(4,6,1);
    graph->addEdge(4,5,1);
    graph->addEdge(5,4,1);
    graph->addEdge(5,6,4);

    graph->floydWarshallShortestPath();
    vector<ulli> poi = {3,5,6};
    auto res = graph->trajectoryOrder(4, poi);

    printTest(res);

}

void printTest(vector<ulli> res){
    for (auto elem : res)
        cout << elem << ' ';
    cout << endl;
}
