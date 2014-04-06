#ifndef KRUSKAL
#define KRUSKAL

#include "../Headers/MyGraph.h"

class Kruskal: public MyGraph
{

public:
	MyGraph* findMST();

};

#endif