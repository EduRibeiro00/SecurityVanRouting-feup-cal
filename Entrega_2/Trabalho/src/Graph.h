/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <iostream>
#include <vector>
#include <queue>
#include <list>
#include <limits>
#include <cmath>
#include <map>
#include <unordered_map>
#include "Node.h"
#include "MutablePriorityQueue.h"


using namespace std;

template <class T> class Edge;
template <class T> class Graph;
template <class T> class Vertex;

struct Key {

	pair<Vertex<Node>*, Vertex<Node>*> keyValue;

	Key(pair<Vertex<Node>*, Vertex<Node>*> key) {
		keyValue = key;
	}

	bool operator==(const Key &other) const {
		return ((keyValue.first == other.keyValue.first)
			 && (keyValue.second == other.keyValue.second));
	}

	int operator() () const {
		return 1;
	}
};


#define INF std::numeric_limits<double>::max()

typedef unordered_map<Key, pair<double, Vertex<Node>*> > Table;
//typedef map<pair<Vertex<Node>*, Vertex<Node>*>, pair<double, Vertex<Node>*>  > Table;

/************************* Vertex **************************/

template <class T>
class Vertex {
	T info;                // contents
	vector<Edge<T> > adj;  // outgoing edges
	bool visited;          // auxiliary field
	double dist = 0;
	Vertex<T> *path = NULL;
	int queueIndex = 0; 		// required by MutablePriorityQueue

	// for calculating the articulation points
	int num;
	int low;
	Vertex<T>* parent;

	bool processing = false;
	void addEdge(Vertex<T> *dest, double w);
	void addEdge(Vertex<T> *dest, double w, bool shouldDisplay);

public:
	Vertex(T in);
	bool operator<(Vertex<T> & vertex) const; // // required by MutablePriorityQueue
	T& getInfo();
	double getDist() const;
	Vertex *getPath() const;
	bool getVisited() const;
	void setVisited(bool visited);
	vector<Edge<T> > getAdj() const;
	void removeEdge(int index);
	friend class Graph<T>;
	friend class MutablePriorityQueue<Vertex<T> >;

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
void Vertex<T>::addEdge(Vertex<T> *dest, double w, bool shouldDisplay) {
	adj.push_back(Edge<T>(dest, w, shouldDisplay));
}

template <class T>
void Vertex<T>::removeEdge(int index) {
	adj.erase(adj.begin() + index);
}

template <class T>
vector<Edge<T> > Vertex<T>::getAdj() const {
	return adj;
}

template <class T>
bool Vertex<T>::getVisited() const {
	return this->visited;
}

template <class T>
void Vertex<T>::setVisited(bool visited) {
	this->visited = visited;
}

template <class T>
bool Vertex<T>::operator<(Vertex<T> & vertex) const {
	return this->dist < vertex.dist;
}

template <class T>
T& Vertex<T>::getInfo() {
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
	Vertex<T> * dest;      	// destination vertex
	double weight;        	// edge weight
	bool shouldDisplay;	// for GraphViewer
public:
	Edge(Vertex<T> *d, double w);
	Edge(Vertex<T> *d, double w, bool shouldDisplay);
	friend class Graph<T>;
	friend class Vertex<T>;
	Vertex<T>* getDest();
	double getWeight();
	bool shouldBeDisplayed();
	void setShouldDisplay(bool display);
};

template <class T>
Edge<T>::Edge(Vertex<T> *d, double w): dest(d), weight(w), shouldDisplay(true) {}

template <class T>
Edge<T>::Edge(Vertex<T> *d, double w, bool shouldDisplay): dest(d), weight(w), shouldDisplay(shouldDisplay) {}


/*************************** Graph  **************************/

template <class T>
class Graph {
	vector<Vertex<T> *> vertexSet;    // vertex set
	double ** W = nullptr; // dist
	int **P = nullptr; // path
	int findVertexIdx(const T &in) const;

	// for calculating articulation points
	int counter = 1;

public:
	Vertex<T> *findVertex(const T &in) const;
	bool addVertex(const T &in);
	bool addEdge(const T &sourc, const T &dest, double w);
	bool addEdge(const T &sourc, const T &dest, double w, bool shouldDisplay);
	int getNumVertex() const;
	vector<Vertex<T> *> getVertexSet() const;
	int getNumEdges() const;
	Edge<T>* getEdge(const T& s, const T& t);

	vector<Vertex<T>* > dfs() const;
	void dfsVisit(Vertex<T> *v, vector<Vertex<T>* > & res) const;


	// Fp05 - single source
	void dijkstraShortestPath(const T &s);
    void dijkstraShortestPathTable(Table &table, const T &s);
	void dijkstraShortestPathOld(const T &s);
	void unweightedShortestPath(const T &s);
	void bellmanFordShortestPath(const T &s);
	vector<T> getPath(const T &origin, const T &dest) const;
	Vertex<T> * initSingleSource(const T &origin);
	bool relax(Vertex<T> *v, Vertex<T> *w, double weight);

	// Fp05 - all pairs
	void floydWarshallShortestPath();
	vector<T> getfloydWarshallPath(const T &origin, const T &dest) const;
	~Graph();


	void resetCounter();
	void calcArticulationPoints(Vertex<T>* v, vector<Vertex<T>* >& res);


	void floydWarshallShortestPathTable(vector<Vertex<T>* > accessNodes, Table& table);

};


// ---------------------------


template <class T>
int Graph<T>::getNumVertex() const {
	return vertexSet.size();
}

template <class T>
vector<Vertex<T> *> Graph<T>::getVertexSet() const {
	return vertexSet;
}

template <class T>
int Graph<T>::getNumEdges() const {
    int total = 0;
    for (auto v : vertexSet) {
        total += v->getAdj().size();
    }
    return total;
}

template <class T>
Edge<T>* Graph<T>::getEdge(const T& s, const T& t) {

	Vertex<T>* source = findVertex(s);
	Vertex<T>* dest = findVertex(t);

	for(auto &e : source->adj)
		if(e.dest == dest)
			return &e;

	return NULL;
}


template <class T>
Vertex<T>*  Edge<T>::getDest(){ return this->dest;}

template <class T>
double Edge<T>::getWeight(){ return this->weight;}


template <class T>
bool Edge<T>::shouldBeDisplayed() {return this->shouldDisplay;}

template <class T>
void Edge<T>::setShouldDisplay(bool display) {
	this->shouldDisplay = display;
}


template <class T>
void Graph<T>::resetCounter() {
	this->counter = 1;
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

template <class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, double w, bool shouldDisplay) {
	auto v1 = findVertex(sourc);
	auto v2 = findVertex(dest);
	if (v1 == NULL || v2 == NULL)
		return false;
	v1->addEdge(v2,w, shouldDisplay);
	return true;
}



template <class T>
vector<Vertex<T>* > Graph<T>::dfs() const {
	vector<Vertex<T>* > res;
	for (auto v : vertexSet)
		v->visited = false;
	for (auto v : vertexSet)
	    if (! v->visited)
	    	dfsVisit(v, res);
	return res;
}



template <class T>
void Graph<T>::dfsVisit(Vertex<T> *v, vector<Vertex<T>* > & res) const {
	v->visited = true;
	res.push_back(v);
	for (auto & e : v->adj) {
		auto w = e.dest;
	    if ( ! w->visited)
	    	dfsVisit(w, res);
	}
}


//--------------------

/**
* Initializes single-source shortest path data (path, dist).
* Receives the content of the source vertex and returns a pointer to the source vertex.
* Used by all single-source shortest path algorithms.
*/

template<class T>
Vertex<T> * Graph<T>::initSingleSource(const T &origin) {
	for (auto v : vertexSet) {
		v->dist = INF;
		v->path = nullptr;
	}
	auto s = findVertex(origin);
	s->dist = 0;
	return s;
}
/**
* Analyzes an edge in single-source shortest path algorithm.
* Returns true if the target vertex was relaxed (dist, path).
* Used by all single-source shortest path algorithms.
*/
template<class T>
bool Graph<T>::relax(Vertex<T> *v, Vertex<T> *w, double weight) {
	if (v->dist + weight < w->dist) {
		w->dist = v->dist + weight;
		w->path = v;
		return true;
	}
	else
		return false;
}

//--------------------

/**************** Single Source Shortest Path algorithms ************/

template<class T>
void Graph<T>::dijkstraShortestPath(const T &origin) {
	auto s = initSingleSource(origin);
	MutablePriorityQueue<Vertex<T> > q;
	q.insert(s);
	while(!q.empty()){
		auto v = q.extractMin();
		for(auto e : v->adj){
		    auto oldDist = e.dest->dist;
			if(relax(v, e.dest, e.weight)){
				if(oldDist == INF)
					q.insert(e.dest);
			}
		}
	}
}


template<class T>
void Graph<T>::dijkstraShortestPathTable(Table &table, const T &origin) {
    auto s = initSingleSource(origin);
    MutablePriorityQueue<Vertex<T> > q;
    q.insert(s);
    while(!q.empty()){

        auto v = q.extractMin();

        if (v != s) {
            table.insert(make_pair(make_pair(s, v), make_pair(v->getDist(), v->getPath())));
        }

        for(auto e : v->adj){

            auto oldDist = e.dest->dist;
            if(relax(v, e.dest, e.weight)){
                if(oldDist == INF)
                    q.insert(e.dest);
            }

        }
    }
}

template<class T>
vector<T> Graph<T>::getPath(const T &origin, const T &dest) const{
	vector<T> res;
	auto v = findVertex(dest);
	if(v == nullptr || v->dist == INF)  //missing or disconected
		return res;
	for( ; v != nullptr; v = v->path)
		res.push_back(v->info);
	reverse(res.begin(), res.end());
	return res;
}

template<class T>
void Graph<T>::unweightedShortestPath(const T &orig) {
	auto s = initSingleSource(orig);
	queue<Vertex<T>*> q;
	q.push(s);
	while(!q.empty()){
		auto v = q.front();
		q.pop();
		for(auto e : v->adj)
			if(relax(v,e.dest,1))
				q.push(e.dest);
	}
}

template<class T>
void Graph<T>::bellmanFordShortestPath(const T &orig) {
	initSingleSource(orig);
	for(unsigned i = 1; i < vertexSet.size(); i++)
		for(auto v : vertexSet)
			for(auto e : v->adj)
				relax(v, e.dest, e.weight);
			for(auto v : vertexSet)
				for(auto e : v->adj)
					if(relax(v, e.dest, e.weight))
						cout << "Negative cycle!" << endl;
}

//---------------------

/*
* Finds the index of the vertex with a given content.
*/
template <class T>
int Graph<T>::findVertexIdx(const T &in) const {
	for (unsigned i = 0; i < vertexSet.size(); i++)
		if (vertexSet[i]->info == in)
			return i;
	return -1;
}
template <class T>
void deleteMatrix(T **m, int n) {
	if (m != nullptr) {
		for (int i = 0; i < n; i++)
			if (m[i] != nullptr)
				delete [] m[i];
		delete [] m;
	}
}
template <class T>
Graph<T>::~Graph() {
	deleteMatrix(W, vertexSet.size());
	deleteMatrix(P, vertexSet.size());
}

//----------------------


/**************** All Pairs Shortest Path  ***************/

template<class T>
void Graph<T>::floydWarshallShortestPath() {
	unsigned n = vertexSet.size();
	deleteMatrix(W, n);
	deleteMatrix(P, n);
	W = new double *[n];
	P = new int *[n];
	for (unsigned i = 0; i < n; i++) {
		W[i] = new double[n];
		P[i] = new int[n];
		for (unsigned j = 0; j < n; j++) {
			W[i][j] = i == j? 0 : INF;
			P[i][j] = -1;
		}
		for (auto e : vertexSet[i]->adj) {
			int j = findVertexIdx(e.dest->info);
			W[i][j] = e.weight;
			P[i][j] = i;
		}
	}

	for(unsigned k = 0; k < n ; k++)
		for(unsigned i = 0; i < n; i++)
			for(unsigned j = 0; j < n; j++){
				if(W[i][k] == INF || W[k][j] == INF)
					continue; //avoid overflow
				int val = W[i][k] + W[k][j];
				if(val < W[i][j]){
					W[i][j] = val;
					P[i][j] = P[k][j];

				}
			}


	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			cout << P[i][j] << " ";
			if(j == n - 1)
				cout << endl;
		}
	}
}

template<class T>
vector<T> Graph<T>::getfloydWarshallPath(const T &orig, const T &dest) const{
	vector<T> res;
	int i = findVertexIdx(orig);
	int j = findVertexIdx(dest);
	if (i == -1 || j == -1 || W[i][j] == INF) // missing or disconnected
		return res;
	for ( ; j != -1; j = P[i][j])
		res.push_back(vertexSet[j]->info);
	reverse(res.begin(), res.end());
	return res;
}


template<class T>
void Graph<T>::floydWarshallShortestPathTable(vector<Vertex<T>* > accessNodes, Table& table) {

	for (auto iVert : accessNodes) {

	    for (auto jVert : accessNodes) {

	        double value;
	        if (iVert == jVert)
	            value = 0;
	        else value = INF;

            table.insert(make_pair(make_pair(iVert, jVert), pair<double, Vertex<T>*>(value, NULL)));

	    }

	    for (auto e : iVert->getAdj()) {

            table[make_pair(iVert, e.getDest())] = make_pair(e.getWeight(), iVert);

        }

	}


    for (auto kVert : accessNodes) {

        for (auto jVert : accessNodes) {

            if (kVert != jVert) {

                for (auto iVert : accessNodes) {

                    if (table.at(make_pair(iVert, kVert)).first == INF ||
                        table.at(make_pair(kVert, jVert)).first == INF)
                        continue; //avoid overflow

                    double val = table.at(make_pair(iVert, kVert)).first + table.at(make_pair(kVert, jVert)).first;

                    if (val < table.at(make_pair(iVert, jVert)).first)
                        table[make_pair(iVert, jVert)] = make_pair(val, table.at(make_pair(kVert, jVert)).second);

                }

            }

        }

    }

/*
    for(Table::iterator it = table.begin(); it != table.end(); it++) {

    	if(it->first.first != it->first.second) {

    		cout << "v1: " << it->first.first->getInfo().getID();
    		cout << "; v2: " << it->first.second->getInfo().getID() << endl;
		    		cout << "dist: " << it->second.first;
		    		cout << "; path: " << it->second.second->getInfo().getID() << endl;
    		if(it->second.second == NULL)
    			cout << "NULL" << endl;

    		cout << "----" << endl;
    	}

    }
*/

}





template<class T>
void Graph<T>::calcArticulationPoints(Vertex<T>* v, vector<Vertex<T>* >& res) {

	v->visited = true;
	v->low = v->num = counter++;

	for(auto e : v->adj) {

		Vertex<T>* w = e.dest;

		if(!w->visited) {

			w->parent = v;
			calcArticulationPoints(w, res);
			v->low = min(v->low, w->low);

			if(w->low >= v->num)
				res.push_back(v);

		}
		else if(v->parent != w)
			v->low = min(v->low, w->num);
	}

}



#endif /* GRAPH_H_ */
