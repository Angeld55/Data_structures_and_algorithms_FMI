#include "GraphAlgorithms.h"
#include "../Edge_list_graph/EdgeListGraph.h"
#include <queue>
#include <stack>
#include <functional>
#include <list>
#include "../Union-find/Union-find.h"

void BFS(const Graph& g, int start, std::vector<int>& order)
{
	if (!g.existsVertex(start))
		return;
	int turn = 1;
	if (order.size() != g.getVertexCount())
		throw "Wrong order array size!";

	std::vector<bool> visited(g.getVertexCount());

	std::queue<int> q;
	q.push(start);
	visited[start] = true;



	while (!q.empty())
	{
		int current = q.front();
		q.pop();

		order[current] = turn;
		//std::cout << current << std::endl; //or some other action

		std::vector<std::pair<int, int>> adj;
		g.getSuccessors(current, adj);

		for (int i = 0; i < adj.size(); i++)
		{
			if (visited[adj[i].first])
				continue;
			visited[adj[i].first] = true;
			q.push(adj[i].first);
		}

		turn++;
	}
}

void DFS(const Graph& g, int start)
{
	if (!g.existsVertex(start))
		return;
	std::vector<bool> visited(g.getVertexCount());

	std::stack<int> s;
	s.push(start);

	while (!s.empty())
	{
		int current = s.top();
		s.pop();
		if (visited[current])
			continue;
		visited[current] = true;
		//std::cout << current << std::endl; //or some other action

		std::vector<std::pair<int, int>> adj;
		g.getSuccessors(current, adj);

		for (int i = 0; i < adj.size(); i++)
			s.push(adj[i].first);
	}

}

bool isConnected(const Graph& g)
{
	if (g.isOriented())
		throw "The graph should not be oriented!";

	std::vector<int> order(g.getVertexCount(), -1);
	BFS(g, 0, order);

	return order.size() == g.getVertexCount();
}

bool containsPath(const Graph& g, int start, int end)
{
	if (!g.existsVertex(start) || !g.existsVertex(end))
		throw "Invalid vertex!";

	std::vector<int> order(g.getVertexCount(), -1);
	BFS(g, start, order);

	return order[end] >= 1;
}

int Dijkstra(const Graph& g, int start, int end, std::vector<int>& path)
{
	std::vector<int> distances(g.getVertexCount(), INT_MAX);
	std::vector<int> prev(g.getVertexCount(), -1);

	struct temp
	{
		int vertex;
		int distFromStart;

		bool operator<(const temp& other) const
		{
			return distFromStart > other.distFromStart;
		}
	};
	std::priority_queue<temp> q;

	distances[start] = 0;
	q.push({ start, 0 });

	while (!q.empty())
	{
		temp currentVertex = q.top();
		if (currentVertex.vertex == end)
		{
			int current = end;
			while (current != start)
			{
				path.push_back(current);
				current = prev[current];
			}
			path.push_back(current);
			std::reverse(path.begin(), path.end());

			return currentVertex.distFromStart;
		}
		q.pop();

		std::vector<std::pair<int, int>> successors;
		g.getSuccessors(currentVertex.vertex, successors);

		for (int i = 0; i < successors.size(); i++)
		{
			int currentSuccessor = successors[i].first;
			int currentWeight = successors[i].second;

			if (distances[currentVertex.vertex] + currentWeight < distances[currentSuccessor])
			{
				// Lazy deletion
				distances[currentSuccessor] = distances[currentVertex.vertex] + currentWeight;
				q.push({ currentSuccessor, distances[currentVertex.vertex] + currentWeight });
				prev[currentSuccessor] = currentVertex.vertex;
			}
		}

	}
	return INT_MAX;
}

int Prim(const Graph& g, Graph& MST)
{
	int mstWeight = 0;
	std::vector<bool>  visited(g.getVertexCount(), false);

	auto comp = [](const std::tuple<int, int, int>& lhs, const std::tuple<int, int, int>& rhs) { return std::get<2>(lhs) > std::get<2>(rhs); };
	std::priority_queue<std::tuple<int, int, int>, std::vector<std::tuple<int, int, int> >, decltype(comp)> q;
	
	// Each tuple looks like this: <start, end, weight>

	q.push(std::make_tuple(0, 0, 0)); //we create a virtal edge -> vertex 0 (the start) with weight 0
	int addedEdges = 0; //because with the first pop we don't insert an edge.

	while (addedEdges < g.getVertexCount() - 1)
	{
		std::tuple<int,int, int> edge = q.top();
		q.pop();
		if (visited[std::get<1>(edge)])
			continue;

		mstWeight += std::get<2>(edge);
		
		if (std::get<0>(edge) != std::get<1>(edge)) //so we don't add the virtual edge
		{
			addedEdges++;
			std::cout << "Edge added: " << std::get<0>(edge) << "---" << std::get<1>(edge) << ", Weight:" <<std::get<2>(edge)<<  std::endl;
			MST.addEdge(std::get<0>(edge), std::get<1>(edge), std::get<2>(edge));
		}
		visited[std::get<1>(edge)] = true;

		std::vector<std::pair<int, int>> successors;
		g.getSuccessors(std::get<1>(edge), successors);

		for (int i = 0; i < successors.size(); i++)
			q.push(std::make_tuple(std::get<1>(edge), successors[i].first, successors[i].second));
	}
	return mstWeight;
}

int Kurskal(const Graph& g, Graph& MST)
{
	int mstWeight = 0;

	// <начало, край, тегло>
	std::vector<std::tuple<int, int, int>> edges;
	
	g.getEdges(edges);

	std::sort(edges.begin(), edges.end(),
		[](const std::tuple<int, int, int>& lhs, const std::tuple<int, int, int>& rhs)
	{
		return std::get<2>(lhs) < std::get<2>(rhs);
	});

	int edgesInculded = 0;

	UnionFind uf(g.getVertexCount());

	for (int i = 0; edgesInculded < g.getVertexCount() - 1 && i < edges.size(); i++)
	{
		std::tuple<int, int, int>& currentEdge = edges[i];
		int start = std::get<0>(currentEdge);
		int end = std::get<1>(currentEdge);
		int weight = std::get<2>(currentEdge);

		if (!uf.Union(start, end)) //checks for a cycle
			continue;
		std::cout << "Edge added: " << start << "---" << end << ", Weight:" << weight << std::endl;
		MST.addEdge(start, end, weight);
		edgesInculded++;
		mstWeight += weight;
	}
	return mstWeight;

}
// Проверка дали в граф има цикъл.
bool DFSrec_containsCycle(const Graph& g, std::vector<bool>& visited, std::vector<bool>& stack, int currentVertex)
{
	visited[currentVertex] = true;
	stack[currentVertex] = true;
	
	std::vector<std::pair<int, int>> successors;
	g.getSuccessors(currentVertex, successors);

	for (int i = 0; i < successors.size(); i++)
	{
		if (stack[successors[i].first])
		{
			std::cout << "Cycle detected! Cycle including edge: " << successors[i].first << std::endl;
			return true;
		}

		if (!visited[successors[i].first])
		{
			bool foundCycle = DFSrec_containsCycle(g, visited, stack, successors[i].first);
			if (foundCycle)
				return true;
		}
	}
	stack[currentVertex] = false;
	return false;
}

bool containsCycle(const Graph& g)
{
	std::vector<bool> visited(g.getVertexCount(), false);
	std::vector<bool> stack(g.getVertexCount(), false);

	for (int i = 0; i < g.getVertexCount(); i++)
	{
		if (!visited[i])
		{
			bool fouldCycle = DFSrec_containsCycle(g, visited, stack, i);

			if (fouldCycle)
				 return true;
		}
	}
	return false;
}

void DFSrec_TopoSort(const Graph& g, std::vector<bool>& visited, std::stack<int>& stack, int currentVertex)
{
	visited[currentVertex] = true;

	std::vector<std::pair<int, int>> successors;
	g.getSuccessors(currentVertex, successors);

	for (int i = 0; i < successors.size(); i++)
	{
		if (!visited[successors[i].first])
			DFSrec_TopoSort(g, visited, stack, successors[i].first);
	}
	stack.push(currentVertex);

}
// Топологично сортиране
void TopoSort(const Graph& g, std::vector<int>& result)
{
	if (containsCycle(g))
		throw "Error! The graph should be acyclic!";

	std::vector<bool> visited(g.getVertexCount(), false);
	std::stack<int> topoSort;

	for (int i = 0; i < visited.size(); i++)
	{
		if (!visited[i])
			DFSrec_TopoSort(g, visited, topoSort, i);
	}

	while (topoSort.size() != 0)
	{
		result.push_back(topoSort.top());
		topoSort.pop();
	}
}