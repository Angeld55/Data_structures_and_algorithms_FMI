#pragma once
#include "..\Graph.h"
#include <list>
class AdjListGraph : public Graph
{
	struct Edge
	{
		int end;
		int weight;
	};
	std::vector<std::list<Edge> > adj;
public:
	AdjListGraph(int n, bool oriented);

	int addVertex(); 

	void addEdge(int start, int end, int weight = 1);
	void removeEdge(int start, int end);

	void getSuccessors(int vertex, std::vector<std::pair<int, int>>& vertexAdj) const;
};
AdjListGraph::AdjListGraph(int n, bool oriented) : Graph(n, oriented), adj(n)
{}
int AdjListGraph::addVertex() //O(1)
{
	adj.push_back(std::list<Edge>());
	vertexCount++;
	return adj.size() - 1;
}
void AdjListGraph::addEdge(int start, int end, int weight) // O(1)
{
	if (!existsVertex(start) || !existsVertex(end))
		throw "Invalid vertices!";
	adj[start].push_back({ end, weight });
	if (!oriented)
		adj[end].push_back({ start, weight });
}
void AdjListGraph::removeEdge(int start, int end) // O(m)
{
	if (!existsVertex(start) || !existsVertex(end))
		throw "Invalid vertices!";

	for (auto it = adj[start].begin(); it != adj[start].end();)
	{
		if (it->end == end)
			it = adj[start].erase(it);
		else
			it++;
	}
	if (oriented)
		return;
	for (auto it = adj[end].begin(); it != adj[end].end();)
	{
		if (it->end == start)
			it = adj[end].erase(it);
		else
			it++;
	}
}
void AdjListGraph::getSuccessors(int vertex, std::vector<std::pair<int, int>>& vertexAdj) const //O(d) d - макс разколоненост на графа.
{
	if (!existsVertex(vertex))
		throw "Invalid vertex!";

	for (auto it = adj[vertex].begin(); it != adj[vertex].end(); it++)
		vertexAdj.push_back(std::make_pair(it->end, it->weight));
}
