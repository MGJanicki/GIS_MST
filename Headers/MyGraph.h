#pragma once

#include <vector>
#include "Edge.h"


class MyGraph
{

private:
	vector<Vertex*> vertexes;
	vector<Edge*> edges;
public:
	MyGraph();
	~MyGraph();
	void addVertex(Vertex *aVertex);
	void addEdge(Edge *aEdge);
	Vertex* findVertex(string aName);
	MyGraph* PrimMST();
	MyGraph* KruskalMST();
	MyGraph* BoruvkaMST();
};
