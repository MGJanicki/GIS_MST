#pragma once

#include <vector>
#include <map>
#include <algorithm>
#include "Edge.h"


#include <ogdf/basic/Graph.h>
#include <ogdf/basic/GraphAttributes.h>
#include <ogdf/layered/SugiyamaLayout.h>
#include <ogdf/layered/OptimalRanking.h>
#include <ogdf/layered/MedianHeuristic.h>
#include <ogdf/layered/OptimalHierarchyLayout.h>
#include <ogdf/planarity/PlanarizationLayout.h>
#include <ogdf/planarity/VariableEmbeddingInserter.h>
#include <ogdf/planarity/FastPlanarSubgraph.h>
#include <ogdf/orthogonal/OrthoLayout.h>
#include <ogdf/planarity/EmbedderMinDepthMaxFaceLayers.h>

class MyGraph
{

protected:
	vector<Vertex*> vertexes;
	vector<Edge*> edges;

	void convertToOGDFGraph();
public:
	MyGraph();
	MyGraph(const MyGraph& aGraph);
	~MyGraph();
	MyGraph* getDeepCopy();
	MyGraph* getDeepCopy(bool aCopyEdges);
	virtual void addVertex(Vertex *aVertex);
	virtual void addEdge(Edge *aEdge);
	virtual MyGraph* findMST(unsigned int aMaxDegree);
	Vertex* findVertex(string aName);
	Edge* findEdge(Vertex *aV1, Vertex *aV2);
	Edge* findEdgeByVerticesNames(string aName1, string aName2);
	vector<Vertex*>& getVertices();
	vector<Edge*>& getEdges();
	vector<Vertex*> getNeighbours(Vertex* aVertex);
	bool hasVertex(Vertex* aVertex);
	bool hasEdge(Edge* aEdge);
	unsigned int getEdgesNumber();
	unsigned int getVerticesNumber();
	void resetVertices(); //'unvisits' all vertices
	void generate(unsigned int m0, unsigned int m, unsigned int aVerticesNumber, unsigned int aMaxEdgeLength);
	void drawGraph();
	friend ostream& MyGraph::operator<<(ostream& out, const MyGraph& aGraph);
};
