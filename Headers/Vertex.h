#ifndef VERTEX
#define VERTEX

#include <string>

using namespace std;

class Vertex
{

private:
	string name;
	bool visited;

public:
	Vertex();
	Vertex(string aName);
	~Vertex();
	string getName();
	void setName(string aName);
	bool isVisited();
	void setVisited(bool aVisited);
};

#endif