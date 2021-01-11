#include "AdjListGraph.h"
#include  "../Algorithms/GraphAlgorithms.h"

AdjListGraph::AdjListGraph(int n, bool oriented) : Graph(n, oriented), adj(n)
{}
int AdjListGraph::addVertex() //O(1)
{
	adj.push_back(std::list<Edge>());
	vertexCount++;
	return adj.size() - 1;
}
void AdjListGraph::removeVertex(int vertex_index)
{
	if (!existsVertex(vertex_index))
		throw "Invalid vertex!";
	adj.erase(adj.begin() + (vertex_index - 1));
	for (auto it = adj.begin(); it != adj.end(); it++)
	{
		for (auto list_it = it->begin(); list_it != it->end();)
		{
			if (list_it->end == vertex_index)
			{
				it->erase(list_it);
				continue;
			}
			if (list_it->end > vertex_index) //update vertecies indexes in edges 
				list_it->end--;
			list_it++;
		}
	}
	vertexCount--;
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
void AdjListGraph::getSuccessors(int vertex, std::vector<std::pair<int, int>>& vertexAdj) const //O(d) d - ���� ������������� �� �����.
{
	if (!existsVertex(vertex))
		throw "Invalid vertex!";

	for (auto it = adj[vertex].begin(); it != adj[vertex].end(); it++)
		vertexAdj.push_back(std::make_pair(it->end, it->weight));
}
void AdjListGraph::getPredeccessors(int vertex, std::vector<std::pair<int, int>>& vertexAdj) const
{
	if (!existsVertex(vertex))
		throw "Invalid vertex!";

	for (int i = 0; i < adj.size(); i++)
	{
		// i == vertex is okay because we can have loops
		for (auto it = adj[i].begin(); it != adj[i].end(); it++)
		{
			if (it->end == vertex)
			{
				vertexAdj.push_back(std::make_pair(i, adj[i].size()));
			}
		}
	}
}
bool AdjListGraph::adjacent(int start, int end) const
{
	if (!existsVertex(start) || !existsVertex(end))
		throw "Invalid vertex!";

	for (auto it = adj[start].begin(); it != adj[start].end(); it++)
	{
		if (it->end == end)
			return true;
	}
	return false;
}

void AdjListGraph::getEdges(std::vector<std::tuple<int, int, int>>& edges) const
{
	for (int i = 0; i < adj.size(); i++)
	{
		for (auto it = adj[i].begin(); it != adj[i].end(); it++)
			edges.push_back(std::make_tuple(i, it->end, it->weight));
	}
}
