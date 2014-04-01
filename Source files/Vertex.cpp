#include "../Headers/Vertex.h"

Vertex::Vertex()
{
	degree = 0;
}

Vertex::Vertex(string aName)
{
	name = aName;
	degree = 0;
}

Vertex::~Vertex()
{
}

string Vertex::getName()
{
	return name;
}

void Vertex::setName(string aName)
{
	name = aName;
}

bool Vertex::isVisited()
{
	return visited;
}

void Vertex::setVisited(bool aVisited)
{
	visited = aVisited;
}

unsigned Vertex::getDegree()
{
	return degree;
}

void Vertex::setDegree(unsigned aDegree)
{
	degree = aDegree;
}