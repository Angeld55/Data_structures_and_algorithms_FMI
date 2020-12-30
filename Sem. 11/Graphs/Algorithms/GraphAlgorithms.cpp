#include "GraphAlgorithms.h"
#include <queue>
#include <stack>
#include <functional>

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