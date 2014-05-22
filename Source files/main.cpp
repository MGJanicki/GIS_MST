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
		//pGraph = new Boruvka();
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
	
	cout << "Would you like to create graph manually? (y/n)";
	cin >> pContinue;
	
	if(pContinue != 'y')
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
	}

	else
	{
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
	}

	cout << "Give a degree constraint ";
	cin >> pMaxegree;

	/*
	MyGraph g;
	Vertex* v1 = new Vertex("a");
	Vertex* v2 = new Vertex("b");
	Vertex* v3 = new Vertex("c");
	Vertex* v4 = new Vertex("d");
	Vertex* v5 = new Vertex("e");
	Vertex* v6 = new Vertex("f");
	Vertex* v7 = new Vertex("g");
	g.addVertex(v1);
	g.addVertex(v2);
	g.addVertex(v3);
	g.addVertex(v4);
	g.addVertex(v5);
	g.addVertex(v6);
	g.addVertex(v7);
	Edge* e1 = new Edge(v1, v2, 7);
	Edge* e2 = new Edge(v2, v3, 11);
	Edge* e3 = new Edge(v3, v5, 5);
	Edge* e4 = new Edge(v1, v4, 4);
	Edge* e5 = new Edge(v2, v4, 9);
	Edge* e6 = new Edge(v2, v5, 10);
	Edge* e7 = new Edge(v4, v5, 15);
	Edge* e8 = new Edge(v5, v6, 12);
	Edge* e9 = new Edge(v5, v7, 8);
	Edge* e10 = new Edge(v6, v7, 13);
	Edge* e11 = new Edge(v4, v6, 6);
	g.addEdge(e1);
	g.addEdge(e2);
	g.addEdge(e3);
	g.addEdge(e4);
	g.addEdge(e5);
	g.addEdge(e6);
	g.addEdge(e7);
	g.addEdge(e8);
	g.addEdge(e9);
	g.addEdge(e10);
	g.addEdge(e11);
	*/
	//Prim g;
	/*Kruskal g;
	Vertex* v1 = new Vertex("a");
	Vertex* v2 = new Vertex("b");
	Vertex* v3 = new Vertex("c");
	Vertex* v4 = new Vertex("d");
	Vertex* v5 = new Vertex("e");
	Vertex* v6 = new Vertex("f");
	Vertex* v7 = new Vertex("g");
	Vertex* v8 = new Vertex("h");
	g.addVertex(v1);
	g.addVertex(v2);
	g.addVertex(v3);
	g.addVertex(v4);
	g.addVertex(v5);
	g.addVertex(v6);
	g.addVertex(v7);
	g.addVertex(v8);
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
	g.addEdge(e1);
	g.addEdge(e2);
	g.addEdge(e3);
	g.addEdge(e4);
	g.addEdge(e5);
	g.addEdge(e6);
	g.addEdge(e7);
	g.addEdge(e8);
	g.addEdge(e9);
	g.addEdge(e10);
	g.addEdge(e11);
	g.addEdge(e12);
	g.addEdge(e13);

	//Boruvka b(g, 2);
	//MyGraph& gg = b.findMST();
	//MyGraph* gg = g.findMST("a", 2);
	MyGraph* gg = g.findMST(2);

	cout << g << endl;
	if(gg != NULL) cout << *gg << endl;*/
	


	//Graph* gf = g.convertToOGDFGraph();
	//g.drawGraph(gf);
	GraphVisualizer gv;
	//gv.drawGraph(gg);
	//Kruskal *g = new Kruskal();
	MyGraph* gg = pGraph->findMST(pMaxegree);
	if(gg != NULL) gv.drawGraphWithMST(*pGraph, *gg);
	else cout << "No solution found\n";
	//gv.drawGraph(*g);
	//if(gg != NULL) gv.drawGraphWithMST(g, *gg);
	//delete(gg);

	system("PAUSE");
	
    return 0;

}