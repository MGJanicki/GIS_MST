#include "../Headers/MyGraph.h"
#include "../Headers/Boruvka.h"
#include <iostream>
#include <stdlib.h>
#include <ogdf/basic/tuples.h>
#include <ogdf/basic/Graph_d.h>
#include <ogdf/planarity/PlanarizationLayout.h>
#include <ogdf/planarity/VariableEmbeddingInserter.h>
#include <ogdf/planarity/FastPlanarSubgraph.h>
#include <ogdf/orthogonal/OrthoLayout.h>
#include <ogdf/planarity/EmbedderMinDepthMaxFaceLayers.h>

using namespace ogdf;
int main(int argc, char* argv[])
{
	MyGraph g;
	Vertex* v1 = new Vertex("a");
	Vertex* v2 = new Vertex("b");
	Vertex* v3 = new Vertex("c");
	Vertex* v4 = new Vertex("d");
	Vertex* v5 = new Vertex("e");
	Vertex* v6 = new Vertex("f");
	Vertex* v7 = new Vertex("g");
	g.addVertex(v1);
	g.addVertex(v2);
	g.addVertex(v3);
	g.addVertex(v4);
	g.addVertex(v5);
	g.addVertex(v6);
	g.addVertex(v7);
	Edge* e1 = new Edge(v1, v2, 7);
	Edge* e2 = new Edge(v2, v3, 11);
	Edge* e3 = new Edge(v3, v5, 5);
	Edge* e4 = new Edge(v1, v4, 4);
	Edge* e5 = new Edge(v2, v4, 9);
	Edge* e6 = new Edge(v2, v5, 10);
	Edge* e7 = new Edge(v4, v5, 15);
	Edge* e8 = new Edge(v5, v6, 12);
	Edge* e9 = new Edge(v5, v7, 8);
	Edge* e10 = new Edge(v6, v7, 13);
	Edge* e11 = new Edge(v4, v6, 6);
	g.addEdge(e1);
	g.addEdge(e2);
	g.addEdge(e3);
	g.addEdge(e4);
	g.addEdge(e5);
	g.addEdge(e6);
	g.addEdge(e7);
	g.addEdge(e8);
	g.addEdge(e9);
	g.addEdge(e10);
	g.addEdge(e11);

	Boruvka b(&g);
	MyGraph* gg = b.findMST();

	cout << g << endl;
	cout << *gg << endl;

	

	system("PAUSE");
 
    return 0;

}