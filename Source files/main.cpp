#include "../Headers/Graph.h"
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
	ogdf::Graph G;
	node n1 = G.newNode();
	node n2 = G.newNode();
	G.newEdge(n1,n2);
	G.newEdge(n1,n2);
	cout << G.numberOfEdges() << endl;
	system("PAUSE");
 
    return 0;

}