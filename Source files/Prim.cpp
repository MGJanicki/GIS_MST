#include "../Headers/Prim.h"

void Prim::addVertex(Vertex *aVertex)
{
	for(vector<Vertex*>::iterator pIterator = vertexes.begin(); pIterator != vertexes.end(); ++pIterator)
	{
		if((*pIterator) == aVertex) return;
	}
	aVertex->setVisited(false);
	vertexes.push_back(aVertex);
	if(vertexEdges.find(aVertex) == vertexEdges.end())
	{
		vector<Edge*> pEdges;
		vertexEdges.insert(make_pair(aVertex, pEdges));
	}
}

void Prim::addEdge(Edge *aEdge)
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

	//add to map containing information about vertex/edges dependency
	vertexEdges.find(aEdge->getVertex1())->second.push_back(aEdge);
	vertexEdges.find(aEdge->getVertex2())->second.push_back(aEdge);
}

MyGraph* Prim::findMST(string aStartVertex)
{
	//set provides every element is unique
	set<Edge*> pEdges;
	MyGraph* pGraph = this->getDeepCopy(false);
	Vertex* pVertex = findVertex(aStartVertex);
	Edge* pShortestEdge;
	if(pVertex == NULL) return NULL;
	do
	{
		//add new vertex edges to set of possible new MST edges
		for(Edge *pEdge: vertexEdges.find(pVertex)->second)
		{
			pEdges.insert(pEdge);
		}

		//find shortest edge which doesn't create a cycle
		pShortestEdge = NULL;
		for (Edge* pEdge: pEdges)
		{
			if((!pEdge->getVertex1()->isVisited() || !pEdge->getVertex2()->isVisited())
				&& (pShortestEdge == NULL || pShortestEdge->getLength() > pEdge->getLength()))
			{
				pShortestEdge = pEdge;
			}
		}

		//if we cannot find a new edge belonging to MST that means a graph isn't connected
		if(pShortestEdge == NULL) break;

		//add new Edge to MST Graph
		Vertex* pNewVertex1 = pGraph->findVertex(pShortestEdge->getVertex1()->getName());
		Vertex* pNewVertex2 = pGraph->findVertex(pShortestEdge->getVertex2()->getName());
		Edge* pNewEdge = new Edge(pNewVertex1, pNewVertex2, pShortestEdge->getLength());
		pGraph->addEdge(pNewEdge);

		if(pShortestEdge->getVertex1()->isVisited()) pVertex = pShortestEdge->getVertex2();
		else pVertex = pShortestEdge->getVertex1();

		//mark vertices as visited
		pShortestEdge->getVertex1()->setVisited(true);
		pShortestEdge->getVertex2()->setVisited(true);

		//in a tree q = n - 1 - stop condition
	}while(pGraph->getEdgesNumber() != (pGraph->getVerticesNumber() - 1));

	//solution found
	if(pGraph->getEdgesNumber() == (pGraph->getVerticesNumber() - 1)) return pGraph;
	//solution not found
	else
	{
		delete pGraph;
		return NULL;
	}
}

MyGraph* Prim::findMST(unsigned int aMaxDegree)
{
	//set provides every element is unique
	set<Edge*> pEdges;
	MyGraph* pGraph = this->getDeepCopy(false);
	//we start from a random vertex
	Vertex* pVertex = vertexes[rand() % vertexes.size()];
	Edge* pShortestEdge;
	Vertex* pNewVertex1;
	Vertex* pNewVertex2;
	if(pVertex == NULL) return NULL;
	do
	{
		//add new vertex edges to set of possible new MST edges
		for(Edge *pEdge: vertexEdges.find(pVertex)->second)
		{
			pEdges.insert(pEdge);
		}

		//find shortest edge which doesn't create a cycle
		pShortestEdge = NULL;
		for (Edge* pEdge: pEdges)
		{
			if((!pEdge->getVertex1()->isVisited() || !pEdge->getVertex2()->isVisited())
				&& (pShortestEdge == NULL || pShortestEdge->getLength() > pEdge->getLength()))
			{
				pNewVertex1 = pGraph->findVertex(pEdge->getVertex1()->getName());
				pNewVertex2 = pGraph->findVertex(pEdge->getVertex2()->getName());
				if((pNewVertex1->getDegree() < aMaxDegree && pNewVertex2->getDegree() < aMaxDegree))
				{
					pShortestEdge = pEdge;
				}
			}
		}

		//if we cannot find a new edge belonging to MST that means a graph isn't connected
		if(pShortestEdge == NULL) break;

		//add new Edge to MST Graph
		
		Edge* pNewEdge = new Edge(pNewVertex1, pNewVertex2, pShortestEdge->getLength());
		pGraph->addEdge(pNewEdge);

		if(pShortestEdge->getVertex1()->isVisited()) pVertex = pShortestEdge->getVertex2();
		else pVertex = pShortestEdge->getVertex1();

		//mark vertices as visited
		pShortestEdge->getVertex1()->setVisited(true);
		pShortestEdge->getVertex2()->setVisited(true);

		//in a tree q = n - 1 - stop condition
	}while(pGraph->getEdgesNumber() != (pGraph->getVerticesNumber() - 1));

	//solution found
	if(pGraph->getEdgesNumber() == (pGraph->getVerticesNumber() - 1)) return pGraph;
	//solution not found
	else
	{
		delete pGraph;
		return NULL;
	}
}