/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>
#include <list>
#include <limits>
#include <cmath>
#include "MutablePriorityQueue.h"

using namespace std;

template <class T> class Edge;
template <class T> class Graph;
template <class T> class Vertex;

#define INF std::numeric_limits<double>::max()

/************************* Vertex  **************************/

template <class T>
class Vertex {
	T info;						// content of the vertex
	vector<Edge<T> > adj;		// outgoing edges
	
	double dist = 0;
	Vertex<T>* path = NULL;
	int queueIndex = 0; 		// required by MutablePriorityQueue

	bool visited = false;		// auxiliary field
	bool processing = false;	// auxiliary field

	void addEdge(Vertex<T> *dest, double w);

public:
	Vertex(T in);
	T getInfo() const;
	double getDist() const;
	Vertex *getPath() const;

	bool operator<(Vertex<T> & vertex) const; // // required by MutablePriorityQueue
	friend class Graph<T>;
	friend class MutablePriorityQueue<Vertex<T>>;
};


template <class T>
Vertex<T>::Vertex(T in): info(in) {}

/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
template <class T>
void Vertex<T>::addEdge(Vertex<T> *d, double w) {
	adj.push_back(Edge<T>(d, w));
}

template <class T>
bool Vertex<T>::operator<(Vertex<T> & vertex) const {
	return this->dist < vertex.dist;
}

template <class T>
T Vertex<T>::getInfo() const {
	return this->info;
}

template <class T>
double Vertex<T>::getDist() const {
	return this->dist;
}

template <class T>
Vertex<T> *Vertex<T>::getPath() const {
	return this->path;
}

/********************** Edge  ****************************/

template <class T>
class Edge {
	Vertex<T> * dest;      // destination vertex
	double weight;         // edge weight
public:
	Edge(Vertex<T> *d, double w);
	friend class Graph<T>;
	friend class Vertex<T>;
};

template <class T>
Edge<T>::Edge(Vertex<T> *d, double w): dest(d), weight(w) {}


/*************************** Graph  **************************/

template <class T>
class Graph {
    private:
        vector<Vertex<T> *> vertexSet;    // vertex set
    public:
        Vertex<T> *findVertex(const T &in) const;
        bool addVertex(const T &in);
        bool addEdge(const T &sourc, const T &dest, double w);
        int getNumVertex() const;
        vector<Vertex<T> *> getVertexSet() const;

        // Fp05 - single source
        void unweightedShortestPath(const T &s);    //TODO...
        void dijkstraShortestPath(const T &s);      //TODO...
        void bellmanFordShortestPath(const T &s);   //TODO...
        vector<T> getPathTo(const T &dest) const;   //TODO...

        // Fp05 - all pairs
        void floydWarshallShortestPath();   //TODO...
        vector<T> getfloydWarshallPath(const T &origin, const T &dest) const;   //TODO...
};

template <class T>
int Graph<T>::getNumVertex() const {
	return vertexSet.size();
}

template <class T>
vector<Vertex<T> *> Graph<T>::getVertexSet() const {
	return vertexSet;
}

/*
 * Auxiliary function to find a vertex with a given content.
 */
template <class T>
Vertex<T> * Graph<T>::findVertex(const T &in) const {
	for (auto v : vertexSet)
		if (v->info == in)
			return v;

	return NULL;
}

/*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
template <class T>
bool Graph<T>::addVertex(const T &in) {
	if ( findVertex(in) != NULL)
		return false;
	vertexSet.push_back(new Vertex<T>(in));
	return true;
}

/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
template <class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, double w) {
	auto v1 = findVertex(sourc);
	auto v2 = findVertex(dest);
	if (v1 == NULL || v2 == NULL)
		return false;
	v1->addEdge(v2,w);
	return true;
}

/**************** Single Source Shortest Path algorithms ************/

template<class T>
void Graph<T>::unweightedShortestPath(const T &orig) {
    for (Vertex<T>* v : vertexSet) {
        v->dist = numeric_limits<double>::max();
        v->path = NULL;
    }

    Vertex<T>* v = findVertex(orig);

    if (v == NULL)
        return;

    v->dist = 0;

    queue<Vertex<T>*> Q;
    Q.push(v);

    while (!Q.empty()) {
        v = Q.front();
        Q.pop();

        for (Edge<T> w : v->adj)
            if (w.dest->getDist() == numeric_limits<double>::max()) {
                Q.push(w.dest);

                w.dest->dist = v->getDist() + 1;
                w.dest->path = v;
            }
    }
}

template<class T>
void Graph<T>::dijkstraShortestPath(const T &origin) {
    for (Vertex<T>* v : vertexSet) {
        v->dist = numeric_limits<double>::max();
        v->path = NULL;
        v->visited = false;
    }

    Vertex<T>* s = findVertex(origin);

    if (s == NULL)
        return;

    s->dist = 0;
    s->queueIndex = 0;
    s->visited = true;

    MutablePriorityQueue<Vertex<T> > Q;
    Q.insert(s);

    while (!Q.empty()) {
        Vertex<T>* v = Q.extractMin();

        for (Edge<T> w : v->adj) {
            if (w.dest->getDist() > v->getDist() + w.weight) {
                w.dest->dist = v->getDist() + w.weight;
                w.dest->path = v;

                if (!w.dest->visited) {
                    w.dest->visited = true;
                    Q.insert(w.dest);
                }

                else
                    Q.decreaseKey(w.dest);
            }
        }
    }
}

template<class T>
void Graph<T>::bellmanFordShortestPath(const T &orig) {
	// TODO
}

template<class T>
vector<T> Graph<T>::getPathTo(const T &dest) const {
    vector<T> res;

    Vertex<T>* v = findVertex(dest);

    if (v == NULL)
        return res;

    res.push_back(v->getInfo());

	while (v->getPath() != NULL) {
        v = v->getPath();
        res.insert(res.begin(), v->getInfo()); // Insert in the beginning of the vector
    }

	return res;
}

/**************** All Pairs Shortest Path  ***************/

template<class T>
void Graph<T>::floydWarshallShortestPath() {
	// TODO
}

template<class T>
vector<T> Graph<T>::getfloydWarshallPath(const T &orig, const T &dest) const{
	vector<T> res;
	// TODO
	return res;
}


#endif /* GRAPH_H_ */
