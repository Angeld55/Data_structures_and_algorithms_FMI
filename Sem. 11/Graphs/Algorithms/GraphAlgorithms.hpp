#include "..\Graph.h"
#include <queue>
#include <stack>
#include <functional>

void BFS(const Graph& g, int start)
{
	if (!g.existsVertex(start))
		return;
	std::vector<bool> visited(g.getVertexCount()); //ffff

	std::queue<int> q;
	q.push(start);
	visited[0] = true;

	while (!q.empty())
	{
		int current = q.front();
		q.pop();

		std::cout << current << std::endl; //or some other action

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
		std::cout << current << std::endl; //or some other action

		std::vector<std::pair<int,int>> adj;
		g.getSuccessors(current, adj);
		for (int i = 0; i < adj.size(); i++)
			s.push(adj[i].first);
	}

}