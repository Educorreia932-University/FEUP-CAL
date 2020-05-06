#include "Graph.h"

#define INF std::numeric_limits<double>::max()

int Graph::getNumVertex() const {
    return vertexSet.size();
}

tabHVertex Graph::getVertexSet() const {
    return vertexSet;
}

/*
 * Auxiliary function to find a vertex with a given content.
 */
Vertex *Graph::findVertex(const ulli &in) const {
    auto *v = new Vertex(in);
    Capsule cv(v);
    auto iterator = vertexSet.find(cv);
    if (iterator == vertexSet.end())
        return nullptr;
    return iterator->getVertex();
}

/*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
bool Graph::addVertex(const Capsule &in) {
    if (vertexSet.find(in) != vertexSet.end())
        return false;

    vertexSet.insert(in);
    return true;
}

/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
bool Graph::addEdge(const ulli &sourc, const ulli &dest, double w, const string &streetName) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;

    v1->addEdge(v2, w, streetName);

    return true;
}

int Graph::findVertexIdx(const int &in) const {
    int i = 0;
    for (auto iter : vertexSet) {
        if (iter.getVertex()->id == in)
            return i;
        i++;
    }
    return -1;
}

int Graph::getElement(int pos) const {
    auto iter = vertexSet.begin();
    for (int i = 0; i < pos; ++i)
        iter++;
    return iter->getVertex()->id;
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

void Graph::floydWarshallShortestPath() {
    int n = vertexSet.size();
    deleteMatrix(dist, n);
    deleteMatrix(pred, n);
    dist = new double *[n];
    pred = new int *[n];
    int i = 0;
    for (auto iter : vertexSet) {
        dist[i] = new double[n];
        pred[i] = new int[n];
        for (unsigned j = 0; j < n; j++) {
            dist[i][j] = i == j ? 0 : INF;
            pred[i][j] = -1;
        }
        for (const auto &e : iter.getVertex()->adj) {
            int j = findVertexIdx(e.dest->id);
            dist[i][j] = e.weight;
            pred[i][j] = i;
        }
        i++;
    }
    for (int k = 0; k < n; k++)
        for (i = 0; i < n; i++)
            for (unsigned j = 0; j < n; j++) {
                if (dist[i][k] == INF || dist[k][j] == INF)
                    continue; // avoid overflow
                double val = dist[i][k] + dist[k][j];
                if (val < dist[i][j]) {
                    dist[i][j] = val;
                    pred[i][j] = pred[k][j];
                }
            }
}

vector<int> Graph::getFloydWarshallPath(const ulli &origin, const ulli &dest) const {
    vector<int> res;
    int i = findVertexIdx(origin);
    int j = findVertexIdx(dest);
    if (i == -1 || j == -1 || dist[i][j] == INF) // missing or disconnected
        return res;
    for (; j != -1; j = pred[i][j])
        res.push_back(getElement(j));
    reverse(res.begin(), res.end());
    return res;
}
