#pragma once
#include "../Headers/MyGraph.h"
#include <vector>

class Boruvka: public MyGraph
{
private:
	MyGraph graph;
	int maxDegree;

	vector<MyGraph*> initializeComponents();
	Edge& findShortestEdgeToAnotherComponent(MyGraph& aActualComponent);
	Vertex& getVertexFromEdgeToAnotherComponent(MyGraph& aActualComponent, Edge& aEdge);
	void mergeComponents(MyGraph& aComponent1, MyGraph& aComponent2);
	void setGraph(MyGraph& aGraph);
public:
	Boruvka(void);
	~Boruvka(void);
	MyGraph* findMST(unsigned int aMaxDegree = INT_MAX);
	
};

