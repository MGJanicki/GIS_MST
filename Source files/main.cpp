#include "../Headers/MyGraph.h"
#include "../Headers/Boruvka.h"
#include "../Headers/GraphVisualizer.h"
#include "../Headers/Prim.h"
#include "../Headers/Kruskal.h"
#include <iostream>
#include <stdlib.h>
#include <ogdf/basic/tuples.h>
#include <ogdf/basic/Graph_d.h>
#include <ogdf/planarity/PlanarizationLayout.h>
#include <ogdf/planarity/VariableEmbeddingInserter.h>
#include <ogdf/planarity/FastPlanarSubgraph.h>
#include <ogdf/orthogonal/OrthoLayout.h>
#include <ogdf/planarity/EmbedderMinDepthMaxFaceLayers.h>

using namespace ogdf;

unsigned int testDC(MyGraph *aMyGraph)
{
	unsigned int i = 1;
	MyGraph *pMyGraph = NULL;
	clock_t pClock = clock();
	while(pMyGraph == NULL)
	{
		i++;
		pMyGraph = aMyGraph->findMST(i);
		aMyGraph->resetVertices();
	}
	pClock = clock() - pClock;
	cout << "Solution found in " << (double)pClock/CLOCKS_PER_SEC << " seconds\n";
	GraphVisualizer pGraphVisualizer;
	pGraphVisualizer.drawGraphWithMST(*aMyGraph, *pMyGraph, "testresult.gml");
	return i;
}

int main(int argc, char* argv[])
{
	MyGraph *pGraph;
	string pName1, pName2;
	int pLength, pAlgorithm;
	unsigned int pMaxegree;
	char pContinue;
	Vertex *pVertex1, *pVertex2;
	Edge *pEdge;
	
	srand(time(NULL));

	cout << "Which algorithm should be used? [0 - Boruvka, 1 - Kruskal, 2 - Prim] ";
	cin >> pAlgorithm;

	switch (pAlgorithm)
	{
	case 0:
		pGraph = new Boruvka();
		break;
	case 1:
		pGraph = new Kruskal();
		break;
	case 2:
		pGraph = new Prim();
		break;
	default:
		cout << "Unknown algorithm - program will terminate\n";
		return -1;
	}
	
	cout << "Would you like to generate graph? (y/n)";
	cin >> pContinue;
	
	if(pContinue == 'y')
	{
		unsigned m, m0, pVerticesCount, pMaxEdgeLength;
		cout << "Give the starting number of vertices ";
		cin >> m0;
		cout << "Give the number of edges which will be added in each step ";
		cin >> m;
		cout << "Give the total number of vertices ";
		cin >> pVerticesCount;
		cout << "Give the maximal edge length ";
		cin >> pMaxEdgeLength;
		pGraph->generate(m0, m, pVerticesCount, pMaxEdgeLength);
		cout << "DC = " << testDC(pGraph) << endl;
		system("PAUSE");
		return 0;
	}

	else
	{
		//test failure for DC = 2, a bridge detected
		Vertex* v1 = new Vertex("a");
		Vertex* v2 = new Vertex("b");
		Vertex* v3 = new Vertex("c");
		Vertex* v4 = new Vertex("d");
		Vertex* v5 = new Vertex("e");
		Vertex* v6 = new Vertex("f");
		pGraph->addVertex(v1);
		pGraph->addVertex(v2);
		pGraph->addVertex(v3);
		pGraph->addVertex(v4);
		pGraph->addVertex(v5);
		pGraph->addVertex(v6);
		Edge* e1 = new Edge(v1, v2, 10);
		Edge* e2 = new Edge(v2, v3, 5);
		Edge* e3 = new Edge(v1, v3, 5);
		Edge* e4 = new Edge(v3, v4, 100);
		Edge* e5 = new Edge(v4, v5, 5); 
		Edge* e6 = new Edge(v4, v6, 5);
		Edge* e7 = new Edge(v5, v6, 10);
		pGraph->addEdge(e1);
		pGraph->addEdge(e2);
		pGraph->addEdge(e3);
		pGraph->addEdge(e4);
		pGraph->addEdge(e5);
		pGraph->addEdge(e6);
		pGraph->addEdge(e7);
		/*Vertex* v1 = new Vertex("a");
		Vertex* v2 = new Vertex("b");
		Vertex* v3 = new Vertex("c");
		Vertex* v4 = new Vertex("d");
		Vertex* v5 = new Vertex("e");
		Vertex* v6 = new Vertex("f");
		Vertex* v7 = new Vertex("g");
		Vertex* v8 = new Vertex("h");
		pGraph->addVertex(v1);
		pGraph->addVertex(v2);
		pGraph->addVertex(v3);
		pGraph->addVertex(v4);
		pGraph->addVertex(v5);
		pGraph->addVertex(v6);
		pGraph->addVertex(v7);
		pGraph->addVertex(v8);
		Edge* e1 = new Edge(v1, v2, 7);
		Edge* e2 = new Edge(v2, v3, 3);
		Edge* e3 = new Edge(v3, v4, 11);
		Edge* e4 = new Edge(v1, v5, 1);
		//Edge* e5 = new Edge(v1, v6, 6);
		Edge* e5 = new Edge(v1, v6, 2); //to test dcmst :)
		Edge* e6 = new Edge(v2, v6, 8);
		Edge* e7 = new Edge(v2, v7, 12);
		Edge* e8 = new Edge(v3, v7, 5);
		Edge* e9 = new Edge(v4, v7, 10);
		Edge* e10 = new Edge(v4, v8, 9);
		Edge* e11 = new Edge(v5, v6, 4);
		Edge* e12 = new Edge(v6, v7, 13);
		Edge* e13 = new Edge(v7, v8, 2);
		pGraph->addEdge(e1);
		pGraph->addEdge(e2);
		pGraph->addEdge(e3);
		pGraph->addEdge(e4);
		pGraph->addEdge(e5);
		pGraph->addEdge(e6);
		pGraph->addEdge(e7);
		pGraph->addEdge(e8);
		pGraph->addEdge(e9);
		pGraph->addEdge(e10);
		pGraph->addEdge(e11);
		pGraph->addEdge(e12);
		pGraph->addEdge(e13);*/


		/*
		while(pContinue == 'y')
		{
			//cout << "Give vertex name ";
			cin >> pName1;
			pVertex1 = new Vertex(pName1);
			pGraph->addVertex(pVertex1);

			//cout << "Do you want to add another vertex? (y/n) ";
			cin >> pContinue;
		}
		pContinue = 'y';
		while(pContinue == 'y')
		{
			//cout << "Give start vertex name ";
			cin >> pName1;
			//cout << "Give destination vertex name ";
			cin >> pName2;
			//cout << "Give distance between vertexes ";
			cin >> pLength;
			if(pLength > 0) 
			{
				pVertex1 = pGraph->findVertex(pName1);
				pVertex2 = pGraph->findVertex(pName2);
				pEdge = new Edge(pVertex1, pVertex2, pLength);
				if((pVertex1 != NULL) && (pVertex2 != NULL)) pGraph->addEdge(pEdge);
			}
			//cout << "Do you want to add another edge? (y/n) ";
			cin >> pContinue;
		}
		*/
	}

	cout << "Give a degree constraint ";
	cin >> pMaxegree;
	GraphVisualizer gv;
	MyGraph* gg = pGraph->findMST(pMaxegree);
	if(gg != NULL) 
	{
		cout << "Solution found" << endl;
		gv.drawGraphWithMST(*pGraph, *gg, "tmp.gml");
	}
	else cout << "No solution found\n";
	system("PAUSE");
    return 0;

}