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
	g.addVertex(v1);
	g.addVertex(v2);
	Edge* e = new Edge(v1, v2, 3);
	g.addEdge(e);
	Vertex* v3 = new Vertex("c");
	Edge* e2 = new Edge(v2, v3, 4);
	g.addEdge(e2);

	Boruvka b(&g);
	MyGraph gg = b.findMST();
	vector<Vertex*> vvv = g.getNeighbours(v2);
	cout << vvv.size() << endl;
	

	

	system("PAUSE");
 
    return 0;

}