#pragma once

#include <vector>
#include <map>
#include "Edge.h"
#include <ogdf/basic/Graph_d.h>
#include <ogdf/basic/tuples.h>

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
	ogdf::Graph* convertToOGDFGraph();
};
