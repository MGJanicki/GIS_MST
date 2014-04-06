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

MyGraph* MyGraph::getDeepCopy()
{
	MyGraph* pNewGraph = new MyGraph();
	map<Vertex*, Vertex*> pVerticesMap; // maps vertices to new Graph vertices
	for(Vertex* pV : this->vertexes)
	{
		Vertex* pNewVertex = new Vertex(*pV);
		pNewVertex->setDegree(0);
		pVerticesMap.insert(pair<Vertex*, Vertex*>(pV, pNewVertex));
		pNewGraph->addVertex(pNewVertex);
	}
	for(Edge* pE : this->edges)
	{
		Edge* pNewEdge = new Edge();
		pNewEdge->setLength(pE->getLength());
		pNewEdge->setVertex1(pVerticesMap[pE->getVertex1()]);
		pNewEdge->setVertex2(pVerticesMap[pE->getVertex2()]);
		pNewGraph->addEdge(pNewEdge);
	}
	return pNewGraph;
}

//function to copy only vertices
MyGraph* MyGraph::getDeepCopy(bool aCopyEdges)
{
	if(aCopyEdges) return getDeepCopy();
	MyGraph* pNewGraph = new MyGraph();
	for(Vertex* pV : this->vertexes)
	{
		Vertex* pNewVertex = new Vertex(*pV);
		pNewVertex->setDegree(0);
		pNewGraph->addVertex(pNewVertex);
	}
	return pNewGraph;
}

void MyGraph::addVertex(Vertex *aVertex)
{
	for(vector<Vertex*>::iterator pIterator = vertexes.begin(); pIterator != vertexes.end(); ++pIterator)
	{
		if((*pIterator) == aVertex) return;
	}
	aVertex->setVisited(false);
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
	aEdge->getVertex1()->setDegree(aEdge->getVertex1()->getDegree() + 1);
	aEdge->getVertex2()->setDegree(aEdge->getVertex2()->getDegree() + 1);
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

Edge* MyGraph::findEdgeByVerticesNames(string aName1, string aName2)
{
	for(Edge* pE : this->edges)
	{
		if((pE->getVertex1()->getName().compare(aName1) == 0 && pE->getVertex2()->getName().compare(aName2) == 0)
			|| (pE->getVertex2()->getName().compare(aName1) == 0 && pE->getVertex1()->getName().compare(aName2) == 0))
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

unsigned int MyGraph::getEdgesNumber()
{
	return edges.size();
}

unsigned int MyGraph::getVerticesNumber()
{
	return vertexes.size();
}

void MyGraph::resetVertices()
{
	for(Vertex* pVertex: vertexes)
	{
		pVertex->setVisited(false);
	}
}

ostream& operator<<(ostream& out, const MyGraph& aGraph)
{
	string result = "";
	for(Vertex* pV : aGraph.vertexes)
	{
		result += pV->getName() + "(" + to_string(pV->getDegree()) + ")" + ",";
	}
	result += "\n";
	for(Edge* pE : aGraph.edges)
	{
		result += pE->getVertex1()->getName() + "-" + to_string(pE->getLength()) + "-" + pE->getVertex2()->getName() + "\n";
	}
	out << result;
	return out;
}