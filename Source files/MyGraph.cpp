#include "../Headers/MyGraph.h"

MyGraph::MyGraph()
{

}

MyGraph::~MyGraph()
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

void MyGraph::addVertex(Vertex *aVertex)
{
	for(vector<Vertex*>::iterator pIterator = vertexes.begin(); pIterator != vertexes.end(); ++pIterator)
	{
		if((*pIterator) == aVertex) return;
	}
	vertexes.push_back(aVertex);
}

void MyGraph::addEdge(Edge *aEdge)
{
	for(vector<Edge*>::iterator pIterator = edges.begin(); pIterator != edges.end(); ++pIterator)
	{
		//krawêdŸ nieskierowana - trzeba sprawdziæ czy graf ju¿ nie zawiera krawêdzi ³¹cz¹cej dan¹ parê wierzcho³ków 
		if(((*pIterator)->getVertex1() == aEdge->getVertex1() && (*pIterator)->getVertex2() == aEdge->getVertex2())
			|| ((*pIterator)->getVertex1() == aEdge->getVertex2() && (*pIterator)->getVertex2() == aEdge->getVertex1()))
			return;
	}
	edges.push_back(aEdge);
}

Vertex* MyGraph::findVertex(string aName)
{
	for(vector<Vertex*>::iterator pIterator = vertexes.begin(); pIterator != vertexes.end(); ++pIterator)
	{
		if(aName == (*pIterator)->getName()) return *pIterator;
	}
}