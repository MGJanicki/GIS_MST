#pragma once
#include "../Headers/MyGraph.h"
#include <vector>

class Boruvka
{
private:
	MyGraph graph;
	int maxDegree;

	vector<MyGraph*> initializeComponents();
	Edge& findShortestEdgeToAnotherComponent(MyGraph& aActualComponent);
	Vertex& getVertexFromEdgeToAnotherComponent(MyGraph& aActualComponent, Edge& aEdge);
	void mergeComponents(MyGraph& aComponent1, MyGraph& aComponent2);
public:
	Boruvka(void);
	Boruvka(MyGraph& aGraph, unsigned aMaxDegree = INT_MAX);
	~Boruvka(void);
	void setGraph(MyGraph& aGraph);
	MyGraph& findMST();
	
};

