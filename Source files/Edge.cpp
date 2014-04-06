#include "../Headers/Edge.h"

Edge::Edge()
{
	vertex1 = NULL;
	vertex2 = NULL;
	length = INT_MAX;
}

Edge::Edge(int aLength)
{
	vertex1 = NULL;
	vertex2 = NULL;
	//zabezpieczenie przed krawêdziami o wagach <= 0
	if(aLength <= 0)
	{
		length = INT_MAX;
	}
	else 
	{
		length = aLength;
	}
}

Edge::Edge(Vertex *aVertex1, Vertex* aVertex2, int aLength)
{
	vertex1 = aVertex1;
	vertex2 = aVertex2;
	if(aLength <= 0)
	{
		length = INT_MAX;
	}
	else 
	{
		length = aLength;
	}
}

Edge::~Edge()
{
}

Vertex* Edge::getVertex1()
{
	return vertex1;
}

void Edge::setVertex1(Vertex *aVertex)
{
	vertex1 = aVertex;
}

Vertex* Edge::getVertex2()
{
	return vertex2;
}

void Edge::setVertex2(Vertex *aVertex)
{
	vertex2 = aVertex;
}

int Edge::getLength()
{
	return length;
}

void Edge::setLength(int aLength)
{
	length = aLength;
}

bool Edge::compare(Edge* aEdge1, Edge* aEdge2)
{
	return (aEdge1->getLength() < aEdge2->getLength());
}