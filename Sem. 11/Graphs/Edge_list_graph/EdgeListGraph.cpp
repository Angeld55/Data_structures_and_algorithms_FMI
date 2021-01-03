#include "EdgeListGraph.h"
#include "GraphAlgorithms.h"

EdgeListGraph::EdgeListGraph(int n, bool oriented) : Graph(n, oriented)
{}

int EdgeListGraph::addVertex()
{
	vertexCount++;
	return vertexCount - 1;
}
void EdgeListGraph::removeVertex(int vertex_index) 
{
	if (!existsVertex(vertex_index))
		throw "Invalid vertex!";
	//remove edges to/from vertex_index
	for (auto it = edges.begin(); it != edges.end(); it++)
	{
		if (it->start == vertex_index || it->end == vertex_index || (!oriented && (it->start == vertex_index || it->end == vertex_index)))
			edges.erase(it);
	}
	vertexCount--;
}
void EdgeListGraph::addEdge(int start, int end, int weight)
{
	if (!existsVertex(start) || !existsVertex(end))
		throw "Invalid vertices!";

	edges.push_back({ start, end, weight });
	if (!oriented)
		edges.push_back({ end, start, weight });
}

void EdgeListGraph::removeEdge(int start, int end) // O(m)
{
	if (!existsVertex(start) || !existsVertex(end))
		throw "Invalid vertices!";

	bool found = false;
	for (auto it = edges.begin(); it != edges.end();)
	{
		if ((it->start == start && it->end == end) || (!oriented && it->start == end && it->end == start))
			it = edges.erase(it);
		else
			it++;
	}
}
void EdgeListGraph::getSuccessors(int vertex, std::vector<std::pair<int, int>>& vertexAdj) const
{
	if (!existsVertex(vertex))
		throw "Invalid vertex!";

	for (auto it = edges.begin(); it != edges.end(); it++)
		if (it->start == vertex)
			vertexAdj.push_back(std::make_pair(it->end, it->weight));
}
void EdgeListGraph::getPredeccessors(int vertex, std::vector<std::pair<int, int>>& vertexAdj) const
{
	if (!existsVertex(vertex))
		throw "Invalid vertex!";

	for (auto it = edges.begin(); it != edges.end(); it++)
		if (it->end == vertex)
			vertexAdj.push_back(std::make_pair(it->start, it->weight));
}
bool EdgeListGraph::adjacent(int start, int end) const
{
	if (!existsVertex(start) || !existsVertex(end))
		throw "Invalid vertex!";

	bool isFound = false;
	for (auto it = edges.begin(); it != edges.end(); it++)
	{
		if (it->start == start && it->end == end)
		{
			isFound = true;
			break;
		}
	}
	return isFound;
}
