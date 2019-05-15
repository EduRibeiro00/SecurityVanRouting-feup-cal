/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>
#include <limits>
#include <cmath>
#include <algorithm>

using namespace std;

template <class T> class Edge;
template <class T> class Graph;

constexpr auto INF = std::numeric_limits<double>::max();

/*
 * ================================================================================================
 * Class Vertex
 * ================================================================================================
 */
template <class T>
class Vertex {
	T info;
	vector<Edge<T> *> outgoing;  // adj
	vector<Edge<T> *> incoming;
	Edge<T> * addEdge(Vertex<T> *dest, double c, double f);
	Vertex(T in);

	bool visited;  // for path finding
	Edge<T> *path; // for path finding

public:
	T getInfo() const;
	vector<Edge<T> *> getAdj() const;
	friend class Graph<T>;
};


template <class T>
Vertex<T>::Vertex(T in): info(in) {
}

template <class T>
Edge<T> *Vertex<T>::addEdge(Vertex<T> *dest, double c, double f) {
	Edge<T> * e = new Edge<T>(this, dest, c, f);
	this->outgoing.push_back(e);
	dest->incoming.push_back(e);
	return e;
}

template <class T>
T Vertex<T>::getInfo() const {
	return this->info;
}

template <class T>
vector<Edge<T> *> Vertex<T>::getAdj() const {
	return this->outgoing;
}


/* ================================================================================================
 * Class Edge
 * ================================================================================================
 */
template <class T>
class Edge {
	Vertex<T> * orig;
	Vertex<T> * dest;
	double capacity;
	double flow;
	Edge(Vertex<T> *o, Vertex<T> *d, double c, double f=0);

public:
	double getFlow() const;
	Vertex<T> *getDest() const;

	friend class Graph<T>;
	friend class Vertex<T>;
};

template <class T>
Edge<T>::Edge(Vertex<T> *o, Vertex<T> *d, double w, double f): orig(o), dest(d), capacity(w), flow(f){}

template <class T>
double Edge<T>::getFlow() const {
	return flow;
}

template <class T>
Vertex<T>* Edge<T>::getDest() const {
	return dest;
}


/* ================================================================================================
 * Class Graph
 * ================================================================================================
 */
template <class T>
class Graph {
	vector<Vertex<T> *> vertexSet;
	Vertex<T>* findVertex(const T &inf) const;
public:
	vector<Vertex<T> *> getVertexSet() const;
	Vertex<T> *addVertex(const T &in);
	Edge<T> *addEdge(const T &sourc, const T &dest, double c, double f=0);
	void fordFulkerson(T source, T target);
	void resetFlows();
    bool findAugmentationPath(Vertex<T>* s, Vertex<T>* t);
    int findMinResidualAlongPath(Vertex<T>* s, Vertex<T>* t);
    void augmentFlowAlongPath(Vertex<T>* s, Vertex<T>* t, int f);
    void testAndVisit(queue<Vertex<T>* >& q, Edge<T>* e, Vertex<T>* w, int residual);
};

template <class T>
Vertex<T> * Graph<T>::addVertex(const T &in) {
	Vertex<T> *v = findVertex(in);
	if (v != nullptr)
		return v;
	v = new Vertex<T>(in);
	vertexSet.push_back(v);
	return v;
}

template <class T>
Edge<T> * Graph<T>::addEdge(const T &sourc, const T &dest, double c, double f) {
	auto s = findVertex(sourc);
	auto d = findVertex(dest);
	if (s == nullptr || d == nullptr)
		return nullptr;
	else
		return s->addEdge(d, c, f);
}

template <class T>
Vertex<T>* Graph<T>::findVertex(const T & inf) const {
	for (auto v : vertexSet)
		if (v->info == inf)
			return v;
	return nullptr;
}

template <class T>
vector<Vertex<T> *> Graph<T>::getVertexSet() const {
	return vertexSet;
}


/**
 * Finds the maximum flow in a graph using the Ford Fulkerson algorithm
 * (with the improvement of Edmonds-Karp).
 * Assumes that the graph forms a flow network from source vertex 's'
 * to sink vertex 't' (distinct vertices).
 * Receives as arguments the source and target vertices (identified by their contents).
 * The result is defined by the "flow" field of each edge.
 */
template <class T>
void Graph<T>::fordFulkerson(T source, T target) {

    resetFlows();
    Vertex<T>* s = findVertex(source);
    Vertex<T>* t = findVertex(target);
    int total = 0;

    while(findAugmentationPath(s, t)) {
        int f = findMinResidualAlongPath(s, t);
        augmentFlowAlongPath(s, t, f);
        total += f;
    }

    cout << "Total : " << total << endl;
}

template <class T>
void Graph<T>::resetFlows() {
    for(auto vertex : vertexSet) {
        for (auto e : vertex->outgoing)
            e->flow = 0;

        for(auto e : vertex->incoming)
            e->flow = 0;
    }
}

template <class T>
bool Graph<T>::findAugmentationPath(Vertex<T>* s, Vertex<T>* t) {

    // Edmonds Karp - breadth-first
    queue<Vertex<T>* > q;

    for(auto v : vertexSet)
        v->visited = false;

    s->visited = true;
    q.push(s);

    while((!q.empty()) && (!t->visited)) {
        Vertex<T>* curVertex = q.front();
        q.pop();

        for(auto e : curVertex->outgoing) // direct residual edges
            testAndVisit(q, e, e->dest, e->capacity - e->flow);

        for(auto e : curVertex->incoming) // reverse residual edges
            testAndVisit(q, e, e->orig, e->flow);
    }

    return t->visited;
}

template <class T>
int Graph<T>::findMinResidualAlongPath(Vertex<T> *s, Vertex<T> *t) {
    int f = INF;
    Vertex<T>* v = t;

    while(v != s) {
        Edge<T>* e = v->path;

        if(e->dest == v) { // direct residual edge
            int newF = e->capacity - e->flow;
            f = f < newF? f : newF;
            v = e->orig;
        }
        else { // reverse residual edge
            int newF = e->flow;
            f = f < newF? f : newF;
            v = e->dest;
        }
    }

    return f;
}

template <class T>
void Graph<T>::augmentFlowAlongPath(Vertex<T>* s, Vertex<T>* t, int f) {
    Vertex<T>* v = t;

    while(v != s) {
        Edge<T>* e = v->path;

        if(e->dest == v) { // direct residual edge
            e->flow += f;
            v = e->orig;
        }
        else { // reverse residual edge
            e->flow -= f;
            v = e->dest;
        }
    }
}



template <class T>
void Graph<T>::testAndVisit(queue<Vertex<T>* >& q, Edge<T>* e, Vertex<T>* w, int residual) {
    if(!w->visited && residual > 0) {
        w->visited = true;
        w->path = e; // previous edge in shortest path
        q.push(w);
    }
}


#endif /* GRAPH_H_ */
