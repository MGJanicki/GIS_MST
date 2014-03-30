#include "../Headers/MyGraph.h"


MyGraph::MyGraph()
{

}

MyGraph::MyGraph(const MyGraph& aGraph)
{
	cout << "konstruktor" << endl;
	for(Vertex* pV : aGraph.vertexes)
	{
		Vertex pNewVertex(*pV);
		this->addVertex(&pNewVertex);
	}
	for(Edge* pE : aGraph.edges)
	{
		Edge pNewEdge(*pE);
		this->addEdge(&pNewEdge);
	}
}

MyGraph::~MyGraph()
{
	for(vector<Vertex*>::iterator pIterator = vertexes.begin(); pIterator != vertexes.end(); ++pIterator)
	{
		if(*pIterator != NULL) delete *pIterator;
	}
	for(vector<Edge*>::iterator pIterator = edges.begin(); pIterator != edges.end(); ++pIterator)
	{
		if(*pIterator != NULL) delete *pIterator;
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
	return NULL;
}

Edge* MyGraph::findEdge(Vertex *aV1, Vertex *aV2)
{
	for(Edge* pE : this->edges)
	{
		if((pE->getVertex1() == aV1 && pE->getVertex2() == aV2) 
			|| (pE->getVertex1() == aV2 && pE->getVertex2() == aV1))
			return pE;
	}
	return NULL;
}

vector<Vertex*>& MyGraph::getVertices()
{
	return this->vertexes;
}

vector<Edge*>& MyGraph::getEdges()
{
	return this->edges;
}

vector<Vertex*> MyGraph::getNeighbours(Vertex* aVertex)
{
	vector<Vertex*> pNeighbours;
	for(Edge* pE : this->edges)
	{
		if(pE->getVertex1() == aVertex) pNeighbours.push_back(pE->getVertex2());
		else if(pE->getVertex2() == aVertex) pNeighbours.push_back(pE->getVertex1());
	}
	return pNeighbours;
}

bool MyGraph::hasVertex(Vertex* aVertex)
{
	for(Vertex* pV : this->vertexes)
	{
		if(pV == aVertex) return true;
	}
	return false;
}

bool MyGraph::hasEdge(Edge* aEdge)
{
	for(Edge* pE : this->edges)
	{
		if(pE == aEdge) return true;
	}
	return false;
}

ogdf::Graph* MyGraph::convertToOGDFGraph()
{
	ogdf::Graph* pGraph = new ogdf::Graph();
	map<Vertex*, ogdf::node> pVerticesMapNodes; // mapuje wierzcholki klasy MyGraph na wierzcholki ogdf::Graph 
	
	for(vector<Vertex*>::iterator pIterator = vertexes.begin(); pIterator != vertexes.end(); ++pIterator)
	{
		ogdf::node node = pGraph->newNode();
		pVerticesMapNodes.insert(std::pair<Vertex*, ogdf::node>(*pIterator, node));
	}
	for(vector<Edge*>::iterator pIterator = edges.begin(); pIterator != edges.end(); ++pIterator)
	{
		ogdf::node node1 = pVerticesMapNodes.find((*pIterator)->getVertex1())->second;
		ogdf::node node2 = pVerticesMapNodes.find((*pIterator)->getVertex2())->second;
		pGraph->newEdge(node1, node2);
	}
	return pGraph;
}

void MyGraph::drawGraph(ogdf::Graph* aGraph)
{

}

ostream& operator<<(ostream& out, const MyGraph& aGraph)
{
	string result = "";
	for(Vertex* pV : aGraph.vertexes)
	{
		result += pV->getName() + ",";
	}
	result += "\n";
	for(Edge* pE : aGraph.edges)
	{
		result += pE->getVertex1()->getName() + "-" + to_string(pE->getLength()) + "-" + pE->getVertex2()->getName() + "\n";
	}
	out << result;
	return out;
}