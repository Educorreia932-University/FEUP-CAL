#include "Graph.h"
#include "FloydStorage.h"

Vertex *Graph::findVertex(const ulli &in) const {
    for (auto v: vertexSet)
        if (v->id == in)
            return v;
    return NULL;
}

bool Graph::addVertex(const ulli &in) {
    if (findVertex(in) != nullptr)
        return false;

    vertexSet.push_back(new Vertex(in));

    return true;
}

bool Graph::addVertex(const ulli &in, const double lon, const double lat) {
    if (findVertex(in) != nullptr)
        return false;

    vertexSet.push_back(new Vertex(in, lon, lat));

    return true;
}


bool Graph::addEdge(const ulli &sourc, const ulli &dest, double w, const string &streetName) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;

    v1->addEdge(v2, w, streetName);

    return true;
}


inline ulli Graph::findVertexIdx(const ulli &in) const {
    int end = vertexSet.size() ;
    int begin = 0 ;
    while (end >= begin) {
        int mid = begin + (end- begin) / 2;
        if (in > vertexSet[mid]->getID()  ) begin = mid +1 ;
        else if (in < vertexSet[mid]->getID() ) end = mid - 1;
        else return mid;
    }

    return -1;
}

template<class T>
void deleteMatrix(T **m, int n) {
    if (m != nullptr) {
        for (int i = 0; i < n; i++)
            if (m[i] != nullptr)
                delete[] m[i];
        delete[] m;
    }
}

Graph::~Graph() {
    deleteMatrix(dist, vertexSet.size());
    deleteMatrix(pred, vertexSet.size());
}

void Graph::sortVertexSet() {
    sort(this->vertexSet.begin(), this->vertexSet.end(), [](Vertex* v1, Vertex* v2){
        return v1->getID() < v2->getID();
    });
}

void Graph::handleFloydWarshall(const string& cityName) {
    auto *fs = new FloydStorage(this);

    if (this->dist != nullptr && this->pred != nullptr)
        return;

    if (fs->isToExecuteFloyd(cityName)) {
        floydWarshallShortestPath();
        unsigned int size = vertexSet.size();       //to avoid calculating the size twice
        fs->storePred(size, cityName);
        fs->storeDest(size, cityName);
    }
}

void Graph::floydWarshallShortestPath() {
    int n = vertexSet.size();

    deleteMatrix(dist, n);
    deleteMatrix(pred, n);

    dist = new double *[n];
    pred = new int *[n];

    for (int i = 0; i < n; i++) {
        dist[i] = new double[n];
        pred[i] = new int[n];

        for (unsigned j = 0; j < n; j++) {
            dist[i][j] = i == j ? 0 : INF;
            pred[i][j] = -1;
        }

        for (const auto &e : vertexSet[i]->adj) {
            int j = findVertexIdx(e.dest->id);
            dist[i][j] = e.weight;
            pred[i][j] = i;
        }
    }

    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (unsigned j = 0; j < n; j++) {
                if (dist[i][k] == INF || dist[k][j] == INF)
                    continue;               // avoid overflow

                double val = dist[i][k] + dist[k][j];

                if (val < dist[i][j]) {
                    dist[i][j] = val;
                    pred[i][j] = pred[k][j];
                }
            }
}

vector<ulli> Graph::getFloydWarshallPath(const ulli &origin, const ulli &dest) const {
    vector<ulli> res;
    int i = findVertexIdx(origin);
    int j = findVertexIdx(dest);

    if (i == -1 || j == -1 || dist[i][j] == INF) // missing or disconnected
        return res;

    for (; j != -1; j = pred[i][j])
        res.push_back(vertexSet[j]->id);

    reverse(res.begin(), res.end());

    res.push_back(dest);

    return res;
}

vector<ulli> Graph::trajectoryOrder(ulli origin, vector<ulli> &poi) {
    vector<ulli> order = {};
    vector<bool> visited(vertexSet.size());
    visited[findVertexIdx(origin)] = true;

    ulli idNext;

    //the poi vector must contain the INDEX of the POIS in the vertexSet
    origin = findVertexIdx(origin);
    for (int i = 0; i < poi.size(); i++){
        poi[i] = findVertexIdx(poi[i]);
    }

    for (int i = 1; i < poi.size(); i++) {
        idNext = nextPoi(origin, poi, visited);                             //get the id of the next poi to be visited
        vector<ulli> floydPath = this->getFloydWarshallPath(vertexSet[origin]->getID(), vertexSet[idNext]->getID());    //path between these two points

        order.insert(order.end(), floydPath.begin(), floydPath.end());          //join the actual path two the vector
        visited[idNext] = true;
        origin = idNext;                                                        //the new vertex now is the origin
    }

    return order;
}

//return the id of the next poi
ulli Graph::nextPoi(const ulli &origin, vector<ulli> &poi, vector<bool> visited) {
    int actualIndex = origin;
    double minWeight = INF;
    ulli selectedPoiIndex = -1;

    for (int i = 0; i < poi.size(); i++) {
        ulli nextVertex = poi[i];

        if (dist[actualIndex][nextVertex] < minWeight && visited[nextVertex] == false) {
            minWeight = dist[actualIndex][nextVertex];
            selectedPoiIndex = nextVertex;
        }
    }

    return selectedPoiIndex;
}

vector<Vertex *> Graph::getVertexSet() {
    return vertexSet;
}






