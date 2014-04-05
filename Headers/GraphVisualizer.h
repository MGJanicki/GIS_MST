#pragma once
#include "MyGraph.h"
#include <ogdf/basic/Graph.h>
#include <ogdf/basic/GraphAttributes.h>

using namespace ogdf;
class GraphVisualizer
{
private:
	MyGraph* myGraph;
	Graph ogdfGraph;
	GraphAttributes attributes;

	node getNodeByLabel(string aLabel);
	void convertToOGDFGraph(MyGraph& aMyGraph);
	void draw();
	
public:
	GraphVisualizer(void);
	~GraphVisualizer(void);
	void drawGraph(MyGraph& aMyGraph);
	void drawGraphWithMST(MyGraph& aMyGraph, MyGraph& aMST);
};