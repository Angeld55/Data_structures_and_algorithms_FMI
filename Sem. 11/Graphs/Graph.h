#pragma once
#include <iostream>
#include <vector>

class Graph
{
protected:
	int vertexCount;
	bool oriented;
	
public:
	Graph(int n, bool oriented) : vertexCount(n), oriented(oriented){}
	
	virtual int addVertex() = 0; //return the index of the new vertex

	virtual void addEdge(int start, int end, int weight = 1) = 0;
	virtual void removeEdge(int start, int end) = 0;

	virtual void getSuccessors(int vertex, std::vector<std::pair<int, int>>& vertexAdj) = 0;
	virtual int getVertexCount();

	bool existsVertex(int vertex);
};
bool Graph::existsVertex(int vertex)
{
	return vertex < vertexCount;
}
int Graph::getVertexCount()
{
	return vertexCount;
}