#include "../Headers/Kruskal.h"

void Kruskal::initialize(MyGraph *aGraph)
{
	vector<Vertex*> pVertices = aGraph->getVertices();
	vector<Vertex*> pNewVertices;
	for(unsigned int i = 0; i < pVertices.size(); i++)
	{
		forest.push_back(pNewVertices);
		forest[i].push_back(pVertices[i]);
	}
}

unsigned int Kruskal::findTree(string aVertexName)
{

	for(unsigned int i = 0; i < forest.size(); i++)
	{
		for(Vertex *pVertex: forest[i])
		{
			if(!aVertexName.compare(pVertex->getName())) return i;
		}
	}
	return INT_MAX;
}

void Kruskal::mergeTrees(unsigned int aTree1, unsigned int aTree2)
{
	//concatenating smaller tree to a bigger one
	if(aTree1 >= aTree2)
	{
		for(Vertex *pVertex: forest[aTree2])
		{
			forest[aTree1].push_back(pVertex);
		}
		forest.erase(forest.begin() + aTree2);
	}
	else
	{
		for(Vertex *pVertex: forest[aTree1])
		{
			forest[aTree2].push_back(pVertex);
		}
		forest.erase(forest.begin() + aTree1);
	}

}

MyGraph* Kruskal::findMST(unsigned int aMaxDegree)
{
	MyGraph* pGraph = getDeepCopy(false);
	sort(edges.begin(), edges.end(), Edge::compare);

	initialize(pGraph);

	unsigned int pTree1, pTree2;

	for(Edge* pEdge: edges)
	{
		pTree1 = findTree(pEdge->getVertex1()->getName());
		pTree2 = findTree(pEdge->getVertex2()->getName());
		//check if new edge doesn't introduce a cycle
		if(pTree1 != pTree2)
		{
			Vertex* pNewVertex1 = pGraph->findVertex(pEdge->getVertex1()->getName());
			Vertex* pNewVertex2 = pGraph->findVertex(pEdge->getVertex2()->getName());

			//add new Edge to MST Graph if degree constraint is fulfilled
			if((pNewVertex1->getDegree() < aMaxDegree && pNewVertex2->getDegree() < aMaxDegree))
			{
				Edge* pNewEdge = new Edge(pNewVertex1, pNewVertex2, pEdge->getLength());
				pGraph->addEdge(pNewEdge);
				//merge trees into one
				mergeTrees(pTree1, pTree2);
			}

			//in a tree q = n - 1 - stop condition
			if(pGraph->getEdgesNumber() == (pGraph->getVerticesNumber() - 1)) break;
		}
	}

	//solution found
	if(pGraph->getEdgesNumber() == (pGraph->getVerticesNumber() - 1)) return pGraph;
	//solution not found
	else 
	{
		delete pGraph;
		return NULL;
	}

}