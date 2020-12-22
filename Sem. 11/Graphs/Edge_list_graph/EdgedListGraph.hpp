#include "..\Graph.h"
#include <list>
class EdgedListGraph : public Graph
{
	struct Edge
	{
		int start;
		int end;
		int weight;
	};
	std::list<Edge> edges;
public:
	EdgedListGraph(int n, bool oriented);
	int addVertex(); //return the index of the new vertex

	void addEdge(int start, int end, int weight = 1);
	void removeEdge(int start, int end);

	void getSuccessors(int vertex, std::vector<std::pair<int, int>>& vertexAdj);
};
EdgedListGraph::EdgedListGraph(int n, bool oriented) : Graph(n, oriented)
{}

int EdgedListGraph::addVertex()
{
	vertexCount++;
	return vertexCount - 1;
}

void EdgedListGraph::addEdge(int start, int end, int weight)
{
	if (!existsVertex(start) || !existsVertex(end))
		throw "Invalid vertices!";

	edges.push_back({ start, end, weight });
	if (!oriented)
		edges.push_back({ end, start, weight });
}

void EdgedListGraph::removeEdge(int start, int end) // O(m)
{
	if (!existsVertex(start) || !existsVertex(end))
		throw "Invalid vertices!";

	bool found = false;
	for (auto it = edges.begin(); it != edges.end(); it++)
	{
		if ((it->start == start && it->end == end) || (!oriented && it->start == end && it->end == start))
			it = edges.erase(it);
	}
}
void EdgedListGraph::getSuccessors(int vertex, std::vector<std::pair<int, int>>& vertexAdj) // O(n+m)
{
	if (!existsVertex(vertex))
		throw "Invalid vertex!";

	for (auto it = edges.begin(); it != edges.end(); it++)
	{
		if (it->start == vertex)
			vertexAdj.push_back(std::make_pair(it->end, it->weight));
	}
}
