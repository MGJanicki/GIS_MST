#include "../Headers/Graph.h"

Graph::Graph()
{

}

Graph::~Graph()
{
	for(vector<Vertex*>::iterator pIterator = vertexes.begin(); pIterator != vertexes.end(); ++pIterator)
	{
		delete *pIterator;
	}
	for(vector<Edge*>::iterator pIterator = edges.begin(); pIterator != edges.end(); ++pIterator)
	{
		delete *pIterator;
	}
}

void Graph::addVertex(Vertex *aVertex)
{
	for(vector<Vertex*>::iterator pIterator = vertexes.begin(); pIterator != vertexes.end(); ++pIterator)
	{
		if((*pIterator) == aVertex) return;
	}
	vertexes.push_back(aVertex);
}

void Graph::addEdge(Edge *aEdge)
{
	for(vector<Edge*>::iterator pIterator = edges.begin(); pIterator != edges.end(); ++pIterator)
	{
		//kraw�d� nieskierowana - trzeba sprawdzi� czy graf ju� nie zawiera kraw�dzi ��cz�cej dan� par� wierzcho�k�w 
		if(((*pIterator)->getVertex1() == aEdge->getVertex1() && (*pIterator)->getVertex2() == aEdge->getVertex2())
			|| ((*pIterator)->getVertex1() == aEdge->getVertex2() && (*pIterator)->getVertex2() == aEdge->getVertex1()))
			return;
	}
	edges.push_back(aEdge);
}

Vertex* Graph::findVertex(string aName)
{
	for(vector<Vertex*>::iterator pIterator = vertexes.begin(); pIterator != vertexes.end(); ++pIterator)
	{
		if(aName == (*pIterator)->getName()) return *pIterator;
	}
}