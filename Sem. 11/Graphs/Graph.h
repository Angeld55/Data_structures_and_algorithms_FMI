#ifndef _GRAPH_
#define _GRAPH_

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
	virtual void removeVertex(int vertex_index) = 0;

	virtual void addEdge(int start, int end, int weight = 1) = 0;

	virtual void getSuccessors(int vertex, std::vector<std::pair<int, int>>& vertexAdj) const = 0;
	virtual void getPredeccessors(int vertex, std::vector<std::pair<int, int>>& vertexAdj) const = 0;
	virtual bool adjacent(int start, int end) const = 0; // returns if there is an edge from start to end but not vice versa
	
	virtual int getVertexCount() const;
	bool existsVertex(int vertex) const;
};

#endif