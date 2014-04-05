#pragma once

#include <vector>
#include <map>
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

private:
	vector<Vertex*> vertexes;
	vector<Edge*> edges;

	void convertToOGDFGraph();
public:
	MyGraph();
	MyGraph(const MyGraph& aGraph);
	~MyGraph();
	MyGraph* getDeepCopy();
	void addVertex(Vertex *aVertex);
	void addEdge(Edge *aEdge);
	Vertex* findVertex(string aName);
	Edge* findEdge(Vertex *aV1, Vertex *aV2);
	Edge* findEdgeByVerticesNames(string aName1, string aName2);
	vector<Vertex*>& getVertices();
	vector<Edge*>& getEdges();
	vector<Vertex*> getNeighbours(Vertex* aVertex);
	bool hasVertex(Vertex* aVertex);
	bool hasEdge(Edge* aEdge);
	MyGraph* PrimMST();
	MyGraph* KruskalMST();
	void drawGraph();
	friend ostream& MyGraph::operator<<(ostream& out, const MyGraph& aGraph);
};
