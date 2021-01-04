#include "GraphAlgorithms.h"
#include <queue>
#include <stack>
#include <functional>
#include <list>

void BFS(const Graph& g, int start, std::vector<int>& order)
{
	if (!g.existsVertex(start))
		return;
	std::vector<bool> visited(g.getVertexCount());

	std::queue<int> q;
	q.push(start);
	visited[start] = true;

	while (!q.empty())
	{
		int current = q.front();
		q.pop();

		order.push_back(current);
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

	}
}

void DFS(const Graph& g, int start, std::vector<int>& order)
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

		order.push_back(current);
		//std::cout << current << std::endl; //or some other action

		std::vector<std::pair<int, int>> adj;
		g.getSuccessors(current, adj);
		for (int i = 0; i < adj.size(); i++)
			s.push(adj[i].first);
	}

}

bool isConnected(const Graph& g)
{
	std::vector<int> order;
	BFS(g, 0, order);

	return order.size() == g.getVertexCount();
}

bool containsPath(const Graph& g, int start, int end)
{
	if (!g.existsVertex(start) || !g.existsVertex(end))
		throw "Invalid vertex!";

	std::vector<int> order;
	BFS(g, start, order);

	for (int i = 0; i < order.size(); i++)
	{
		if (order[i] == end)
			return true;
	}
	return false;
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
			std::cout << "Edge added:" << std::get<0>(edge) << " " << std::get<1>(edge) << std::endl;
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

