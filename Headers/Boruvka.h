#pragma once
#include "../Headers/MyGraph.h"

class Boruvka
{
private:
	MyGraph graph;
	int maxDegree;
public:
	Boruvka(void);
	Boruvka(MyGraph* aGraph, unsigned aMaxDegree = INT_MAX);
	~Boruvka(void);

	void setGraph(MyGraph* aGraph);
	MyGraph* findMST();
	vector<MyGraph*> initializeComponents();
	Edge* findShortestEdgeToAnotherComponent(MyGraph* aActualComponent);
	Vertex* getVertexFromEdgeToAnotherComponent(MyGraph* aActualComponent, Edge* aEdge);
	void mergeComponents(MyGraph* aComponent1, MyGraph* aComponent2);
};

