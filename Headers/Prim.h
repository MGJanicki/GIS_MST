#ifndef PRIM
#define PRIM

#include "../Headers/MyGraph.h"
#include <set>

class Prim: public MyGraph
{
private:
	map<Vertex*, vector<Edge*>> vertexEdges;
public:
	MyGraph* findMST(string aStartVertex);
	MyGraph* findMST(unsigned int aMaxDegree);
	void addVertex(Vertex *aVertex);
	void addEdge(Edge *aEdge);
};

#endif