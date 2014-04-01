#include "../Headers/Boruvka.h"
#include <vector>

Boruvka::Boruvka(void)
{
}

Boruvka::Boruvka(MyGraph* aGraph, unsigned aMaxDegree)
{
	this->setGraph(aGraph);
	this->maxDegree = aMaxDegree;
}


Boruvka::~Boruvka(void)
{
}

void Boruvka::setGraph(MyGraph* aGraph)
{
	this->graph = *(aGraph->getDeepCopy());
}

MyGraph* Boruvka::findMST()
{
	vector<MyGraph*> pComponents = this->initializeComponents();
	while(pComponents.size() > 1)
	{
		for(MyGraph* pCompon : pComponents)
		{
			
			if(pCompon == NULL) continue;
			cout << *pCompon << endl;
			Edge* pShortestEdge = this->findShortestEdgeToAnotherComponent(pCompon);
			Vertex* pVertexFromOtherComponent = this->getVertexFromEdgeToAnotherComponent(pCompon, pShortestEdge);

			for(auto pIterator = pComponents.begin(); pIterator != pComponents.end(); ++pIterator)
			{
				if(*pIterator == NULL) continue;
				if((*pIterator)->hasVertex(pVertexFromOtherComponent))
				{
					this->mergeComponents(pCompon, *pIterator);
					pCompon->addEdge(pShortestEdge);
					*pIterator = NULL;
					break;
				}
			}
		}
		pComponents.erase(std::remove(pComponents.begin(), pComponents.end(), nullptr), pComponents.end());
	} 
	return pComponents[0]->getDeepCopy();
}

vector<MyGraph*> Boruvka::initializeComponents()
{
	vector<MyGraph*> pComponents;
	for(Vertex* pV : this->graph.getVertices())
	{
		MyGraph* pG = new MyGraph();
		pV->setDegree(0);
		pG->addVertex(pV);
		pComponents.push_back(pG);
	}
	return pComponents;
}

Edge* Boruvka::findShortestEdgeToAnotherComponent(MyGraph* aActualComponent)
{
	Edge* pShortestEdge = NULL;
	for(Vertex* pActualVertex : aActualComponent->getVertices())
	{
		if(pActualVertex->getDegree() >= this->maxDegree) continue;
		vector<Vertex*> pNeighbours = this->graph.getNeighbours(pActualVertex);
		for(Vertex* pNeigh : pNeighbours)
		{
			if(aActualComponent->hasVertex(pNeigh)) continue;
			Edge* pActualEdge = this->graph.findEdge(pActualVertex, pNeigh);
			if(pActualEdge->getVertex1()->getDegree() == this->maxDegree ||
				pActualEdge->getVertex2()->getDegree() == this->maxDegree)
			{
				pActualEdge = NULL;
				continue;
			}
			if(pShortestEdge == NULL)
			{
				pShortestEdge = pActualEdge;
			}
			else
			{
				bool pActualEdgeIsShortest = pActualEdge->getLength() < pShortestEdge->getLength();
				if(pActualEdgeIsShortest)
				{
					pShortestEdge = pActualEdge;
				}
			}
		}
	}
	return pShortestEdge;
}

Vertex* Boruvka::getVertexFromEdgeToAnotherComponent(MyGraph* aActualComponent, Edge* aEdge)
{
	Vertex* pVertexFromOtherComponent = NULL;
	bool pComponentContainsFirstVertex = aActualComponent->hasVertex(aEdge->getVertex1());
	if(pComponentContainsFirstVertex)
	{
		pVertexFromOtherComponent = aEdge->getVertex2();
	}
	else
	{
		pVertexFromOtherComponent = aEdge->getVertex1();
	}
	return pVertexFromOtherComponent;
}

void Boruvka::mergeComponents(MyGraph* aComponent1, MyGraph* aComponent2)
{
	for(Vertex* pV : aComponent2->getVertices())
	{
		if(!aComponent1->hasVertex(pV)) aComponent1->addVertex(pV);
	}
	for(Edge *pE : aComponent2->getEdges())
	{
		if(!aComponent1->hasEdge(pE)) 
		{
			pE->getVertex1()->setDegree(pE->getVertex1()->getDegree() -1 );
			pE->getVertex2()->setDegree(pE->getVertex2()->getDegree() -1 );
			aComponent1->addEdge(pE);
		}
	}
}