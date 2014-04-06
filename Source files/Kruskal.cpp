#include "../Headers/Kruskal.h"

MyGraph* Kruskal::findMST()
{
	MyGraph* pGraph = getDeepCopy(false);
	sort(edges.begin(), edges.end(), Edge::compare);

	for(Edge* pEdge: edges)
	{
		if(!pEdge->getVertex1()->isVisited() || !pEdge->getVertex2()->isVisited())
		{
			//mark vertices as visited
			pEdge->getVertex1()->setVisited(true);
			pEdge->getVertex2()->setVisited(true);

			//add new Edge to MST Graph
			Vertex* pNewVertex1 = pGraph->findVertex(pEdge->getVertex1()->getName());
			Vertex* pNewVertex2 = pGraph->findVertex(pEdge->getVertex2()->getName());
			Edge* pNewEdge = new Edge(pNewVertex1, pNewVertex2, pEdge->getLength());
			pGraph->addEdge(pNewEdge);

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