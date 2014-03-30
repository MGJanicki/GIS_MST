#include "../Headers/Boruvka.h"
#include <vector>

Boruvka::Boruvka(void)
{
}

Boruvka::Boruvka(MyGraph* aGraph)
{
	this->graph = aGraph;
}


Boruvka::~Boruvka(void)
{
}

void Boruvka::setGraph(MyGraph* aGraph)
{
	this->graph = aGraph;
}

MyGraph Boruvka::findMST()
{
	MyGraph pMst;
	vector<MyGraph*> pComponents;
	for(vector<Vertex*>::iterator pIterator = this->graph->getVertices().begin(); pIterator != this->graph->getVertices().end(); ++pIterator)
	{
		MyGraph* pG = new MyGraph();
		pG->addVertex(*pIterator);
		pComponents.push_back(pG);
		
	}
	//while(pComponents.size() > 1)
	{
		for(MyGraph* pG : pComponents)
		{
			cout << pG->getVertices().size() << endl;
			Edge* pShortestEdge = NULL;
			for(Vertex* pV : pG->getVertices())
			{
				// get all the neighbours of vertex
				vector<Vertex*> pNeighbours = this->graph->getNeighbours(pV);
				for(Vertex* pNeigh : pNeighbours)
				{
					if(pG->hasVertex(pNeigh)) continue;
					Edge* pEdge = this->graph->findEdge(pV, pNeigh);
					if(pShortestEdge == NULL) pShortestEdge = pEdge;
					else if(pEdge->getLength() < pShortestEdge->getLength()) pShortestEdge = pEdge;
				}
			}
			// get vertex form shortes edge which belongs to other component
			Vertex* pVertexFromOtherComponent = NULL;
			if(pG->hasVertex(pShortestEdge->getVertex1())) pVertexFromOtherComponent = pShortestEdge->getVertex2();
			else pVertexFromOtherComponent = pShortestEdge->getVertex1();

			// get component which shortes edge belongs to
			MyGraph* pOtherComponent = NULL;
			int pComponentToErase = 0;
			for(auto pIterator = pComponents.begin(); pIterator != pComponents.end(); ++pIterator)
			{
				if((*pIterator)->hasVertex(pVertexFromOtherComponent))
				{
					this->mergeComponents(pG, *pIterator);
					//pIterator = pComponents.erase(pIterator);
					break;
				}
				pComponentToErase++;
			}
			
			/*for(MyGraph* pTmpComponent : pComponents)
			{
				if(pTmpComponent->hasVertex(pVertexFromOtherComponent))
				{
					pOtherComponent = pTmpComponent;
					break;
				}
			}
			pG = this->mergeComponents(pG, pOtherComponent);*/
		}
	}
	return pMst;
}

void Boruvka::mergeComponents(MyGraph* aComponent1, MyGraph* aComponent2)
{
	for(Vertex* pV : aComponent2->getVertices())
	{
		if(!aComponent1->hasVertex(pV)) aComponent1->addVertex(pV);
	}
	for(Edge *pE : aComponent2->getEdges())
	{
		if(!aComponent1->hasEdge(pE)) aComponent2->addEdge(pE);
	}
}