
#include "UserInterface/UserInterface.h"
#include <iostream>
#include "GraphFactory.h"

using namespace std;

void printTest(vector<ulli> res);
void test1_floyd();
void test2_floyd();

int main() {
    UserInterface ui;
    //ui.mainMenuSelection(ui.showMainMenu());
    auto *g = new GraphFactory();
    g->readVertex("../../utils/map_extraction/nodes.csv");

    test2_floyd();

    return 0;
}


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

void printTest(vector<ulli> res){
    for (auto elem : res)
        cout << elem << ' ';
    cout << endl;
}
