#include "../Headers/Boruvka.h"

Boruvka::Boruvka(void)
{
}

Boruvka::~Boruvka(void)
{
}

void Boruvka::setGraph(MyGraph& aGraph)
{
	this->graph = *(aGraph.getDeepCopy());
}

MyGraph* Boruvka::findMST(unsigned int aMaxDegree)
{
	this->maxDegree = aMaxDegree;
	this->graph = *(this->getDeepCopy());

	vector<MyGraph*> pComponents = this->initializeComponents();
	while(pComponents.size() > 1)
	{
		for(MyGraph* pCompon : pComponents)
		{
			if(pCompon == NULL) continue;
			Edge* pShortestEdge = &this->findShortestEdgeToAnotherComponent(*pCompon);
			if(pShortestEdge == NULL) return(NULL);
			Vertex* pVertexFromOtherComponent = &this->getVertexFromEdgeToAnotherComponent(*pCompon, *pShortestEdge);

			for(auto pIterator = pComponents.begin(); pIterator != pComponents.end(); ++pIterator)
			{
				if(*pIterator == NULL) continue;
				if((*pIterator)->hasVertex(pVertexFromOtherComponent))
				{
					this->mergeComponents(*pCompon, **pIterator);
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

Edge& Boruvka::findShortestEdgeToAnotherComponent(MyGraph& aActualComponent)
{
	Edge* pShortestEdge = NULL;
	for(Vertex* pActualVertex : aActualComponent.getVertices())
	{
		if(pActualVertex->getDegree() == this->maxDegree) continue;
		vector<Vertex*> pNeighbours = this->graph.getNeighbours(pActualVertex);
		for(Vertex* pNeigh : pNeighbours)
		{
			if(aActualComponent.hasVertex(pNeigh)) continue;
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
	return *pShortestEdge;
}

Vertex& Boruvka::getVertexFromEdgeToAnotherComponent(MyGraph& aActualComponent, Edge& aEdge)
{
	Vertex* pVertexFromOtherComponent = NULL;
	bool pComponentContainsFirstVertex = aActualComponent.hasVertex(aEdge.getVertex1());
	if(pComponentContainsFirstVertex)
	{
		pVertexFromOtherComponent = aEdge.getVertex2();
	}
	else
	{
		pVertexFromOtherComponent = aEdge.getVertex1();
	}
	return *pVertexFromOtherComponent;
}

void Boruvka::mergeComponents(MyGraph& aComponent1, MyGraph& aComponent2)
{
	for(Vertex* pV : aComponent2.getVertices())
	{
		if(!aComponent1.hasVertex(pV)) aComponent1.getVertices().push_back(pV);
	}
	for(Edge *pE : aComponent2.getEdges())
	{
		if(!aComponent1.hasEdge(pE)) aComponent1.getEdges().push_back(pE);
	}
}