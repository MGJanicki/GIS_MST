#include "../Headers/Vertex.h"

Vertex::Vertex()
{
}

Vertex::Vertex(string aName)
{
	name = aName;
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