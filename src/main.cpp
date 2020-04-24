#include <iostream>
#include "GraphFactory.h"

int main() {
    GraphFactory *g = new GraphFactory();
    g->readEdges("merada.csv");
    return 0;
}
