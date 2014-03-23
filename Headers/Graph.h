#ifndef GRAPH
#define GRAPH

#include <vector>
#include "Edge.h"

class Graph
{

private:
	vector<Vertex*> vertexes;
	vector<Edge*> edges;
public:
	Graph();
	~Graph();
	void addVertex(Vertex *aVertex);
	void addEdge(Edge *aEdge);
	Vertex* findVertex(string aName);
	Graph* PrimMST();
	Graph* KruskalMST();
	Graph* BoruvkaMST();
};

#endif GRAPH