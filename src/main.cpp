
#include "UserInterface/UserInterface.h"
#include "Graph/GraphFactory.h"
#include "Graph/PoiStorage.h"

using namespace std;

void printTest(vector<ulli> res);
void test1_floyd();
void test2_floyd();
void test1_trajectoryOrder();
void test_sortVertexSet(Graph graph);

int main() {
    // Creating graph
    GraphFactory graphFactory;

    graphFactory.readVertex("../data/nodes_PORTO.csv");
    graphFactory.readEdges("../data/edges_PORTO.csv");

    Graph graph = graphFactory.graph;

    // Reading POIs
    auto* poiStorage = new PoiStorage("PORTO");

    if (!poiStorage->readPois()){
        ERROR("Not possible to read POIS");
        exit(1);
    }

    //initiating the interface
    UserInterface ui(&graph, poiStorage);
    ui.mainMenuSelection();

    // test1_trajectoryOrder();
    // test the floyd warshall greedy aproach

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
    //auto res = graph->trajectoryOrder(4, poi);

    //printTest(res);

}

void test_sortVertexSet(Graph graph){
    vector<Vertex*> v = graph.getVertexSet();
    for (int i = 0 ; i < 5; i++){
        cout << v[i]->getID() << endl;
    }
}

void printTest(vector<ulli> res){
    for (auto elem : res)
        cout << elem << ' ';
    cout << endl;
}
