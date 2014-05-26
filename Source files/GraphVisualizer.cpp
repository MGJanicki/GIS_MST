#include "../Headers/GraphVisualizer.h"

GraphVisualizer::GraphVisualizer(void)
{
	GraphAttributes GA(this->ogdfGraph, GraphAttributes::nodeGraphics |	
		GraphAttributes::edgeGraphics | GraphAttributes::nodeLabel | GraphAttributes::edgeLabel 
		| GraphAttributes::nodeColor | GraphAttributes::edgeColor );
	this->attributes = GA;
}

GraphVisualizer::~GraphVisualizer(void)
{
}

node GraphVisualizer::getNodeByLabel(string aLabel)
{
	node v;
	forall_nodes(v, this->ogdfGraph)
	{
		if(this->attributes.labelNode(v) == String(aLabel.c_str()))
			return v;
	}
	return NULL;
}

void GraphVisualizer::drawGraph(MyGraph& aMyGraph, ogdf::String pFilename)
{
	this->convertToOGDFGraph(aMyGraph);
	this->draw(pFilename);
}

void GraphVisualizer::drawGraphWithMST(MyGraph& aMyGraph, MyGraph& aMST, ogdf::String pFilename)
{
	this->convertToOGDFGraph(aMyGraph);
	for(Edge* pE : aMST.getEdges())
	{
		//Edge* pEdge = aMyGraph.findEdgeByVerticesNames(pE->getVertex1()->getName(), pE->getVertex2()->getName());
		string pLabel1 = pE->getVertex1()->getName();
		string pLabel2 = pE->getVertex2()->getName();
		edge Edge = this->ogdfGraph.searchEdge(this->getNodeByLabel(pLabel1), this->getNodeByLabel(pLabel2));
		this->attributes.colorEdge(Edge) = "#ff0000";
	}
	this->draw(pFilename);
}

void GraphVisualizer::draw(ogdf::String pFilename)
{
	PlanarizationLayout pl;
	
	FastPlanarSubgraph *ps = new FastPlanarSubgraph;
    ps->runs(100);
	VariableEmbeddingInserter *ves = new VariableEmbeddingInserter;
    ves->removeReinsert(EdgeInsertionModule::rrAll);
    pl.setSubgraph(ps);
    pl.setInserter(ves);

	EmbedderMinDepthMaxFaceLayers *emb = new EmbedderMinDepthMaxFaceLayers;
    pl.setEmbedder(emb);
	OrthoLayout *ol = new OrthoLayout;
    ol->separation(40.0);
    ol->cOverhang(0.4);
    ol->setOptions(2+4);
    pl.setPlanarLayouter(ol);
 
	pl.call(this->attributes);
 
	attributes.writeGML(pFilename);
	//system("gml2pic -curve cubic test.gml");
}

void GraphVisualizer::convertToOGDFGraph(MyGraph& aMyGraph)
{
	map<Vertex*, node> pVerticesMapNodes; // mapuje wierzcholki klasy MyGraph na wierzcholki ogdf::Graph 
	map<Edge*, edge> pEdgesMap; // mapuje krawedzie klasy MyGraph na krawedzie ogdf::Graph. Potrzebne do pokolorowania krawedzi
	
	for(Vertex* pV : aMyGraph.getVertices())
	{
		node pNode = this->ogdfGraph.newNode();
		this->attributes.labelNode(pNode) = String(pV->getName().c_str());
		this->attributes.shapeNode(pNode) = GraphAttributes::oval;
		this->attributes.colorNode(pNode) = "#00ffff";
		pVerticesMapNodes.insert(pair<Vertex*, node>(pV, pNode));
	}
	for(Edge* pE : aMyGraph.getEdges())
	{
		node pNode1 = pVerticesMapNodes.find(pE->getVertex1())->second;
		node pNode2 = pVerticesMapNodes.find(pE->getVertex2())->second;
		edge pEdge = this->ogdfGraph.newEdge(pNode1, pNode2);
		this->attributes.labelEdge(pEdge) = String(to_string(pE->getLength()).c_str());
		pEdgesMap.insert(pair<Edge*, edge>(pE, pEdge));
	}
	this->attributes.setAllHeight(30);
	this->attributes.setAllWidth(30);
	this->attributes.directed(false);
}
