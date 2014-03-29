#pragma once
#include <ogdf/basic/Graph_d.h>
#include "../Headers/MyGraph.h"

class GraphConverter
{
public:
	ogdf::Graph* convertToOGDFGrapf(MyGraph* g);
private:
	GraphConverter(void);
	~GraphConverter(void);
};

