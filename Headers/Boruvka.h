#pragma once
#include "../Headers/MyGraph.h"

class Boruvka
{
private:
	MyGraph* graph;
public:
	Boruvka(void);
	Boruvka(MyGraph* aGraph);
	~Boruvka(void);

	void setGraph(MyGraph* aGraph);
	MyGraph findMST();
	void mergeComponents(MyGraph* aComponent1, MyGraph* aComponent2);
};

