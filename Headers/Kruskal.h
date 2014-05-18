#ifndef KRUSKAL
#define KRUSKAL

#include "../Headers/MyGraph.h"

class Kruskal: public MyGraph
{

	vector<vector<Vertex*>> forest;
	void initialize(MyGraph *aGraph);
	unsigned int findTree(string aVertexName);
	void mergeTrees(unsigned int aTree1, unsigned int aTree2);

public:
	MyGraph* findMST(unsigned int aMaxDegree = INT_MAX);

};

#endif