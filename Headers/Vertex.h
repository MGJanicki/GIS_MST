#ifndef VERTEX
#define VERTEX

#include <string>

using namespace std;

class Vertex
{

private:
	string name;
	bool visited;
	unsigned degree;

public:
	Vertex();
	Vertex(string aName);
	~Vertex();
	string getName();
	void setName(string aName);
	bool isVisited();
	void setVisited(bool aVisited);
	unsigned getDegree();
	void setDegree(unsigned aDegree);
};

#endif