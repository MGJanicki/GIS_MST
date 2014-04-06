#pragma once
#include "Vertex.h"

using namespace std;

class Edge
{

private:
	Vertex *vertex1, *vertex2;
	int length;

public:
	Edge();
	Edge(int aLength);
	Edge(Vertex* aVertex1, Vertex* aVertex2, int aLength);
	~Edge();
	Vertex* getVertex1();
	void setVertex1(Vertex* aVertex);
	Vertex* getVertex2();
	void setVertex2(Vertex* aVertex);
	int getLength();
	void setLength(int aLength);
	static bool compare(Edge* aEdge1, Edge* aEdge2);
};