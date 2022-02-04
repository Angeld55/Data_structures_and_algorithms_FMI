
#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <list>
#include <unordered_map>
#include <iterator>
#include <algorithm>
#include <queue>

class Graph
{
public:
	int n;
	std::vector<std::vector<int>> adj;
	Graph(int n) : n(n), adj(n) {}

	void addEdge(int start, int end)
	{
		adj[start].push_back(end);
		adj[end].push_back(start);
	}
};


std::vector<int> bfs(int start, std::vector<bool>& visited, const Graph& g)
{
	std::vector<int> currentComponent;
	std::queue<int> q;
	q.push(start);

	while (!q.empty())
	{
		int current = q.front();
		q.pop();

		if(visited[current])
			continue;
			
		currentComponent.push_back(current);
		visited[current] = true;
	
		for (int i = 0; i < g.adj[current].size(); i++)
		{
			if(!visited[g.adj[current][i]])
				q.push(g.adj[current][i]);
		}

	}

	return std::move(currentComponent);

}
std::vector<std::vector<int>> getConnectedComponents(const Graph& g)
{
	std::vector<bool> visited(g.n);
	std::vector<std::vector<int>> connectedComponents;

	for (int i = 0; i < visited.size(); i++)
	{
		if (!visited[i])
			connectedComponents.push_back(bfs(i, visited, g));
	}

	std::sort(connectedComponents.begin(), connectedComponents.end(),
		[](const std::vector<int>& lhs, const std::vector<int>& rhs)
		{
			return lhs.size() < rhs.size();
		});

	return connectedComponents;
}

int main()
{
	Graph g(6);

	g.addEdge(0, 1);

	g.addEdge(2, 4);
	g.addEdge(2, 3);
	g.addEdge(3, 4);

	auto res = getConnectedComponents(g);

	for (size_t i = 0; i < res.size(); i++)
	{
		for (size_t j = 0; j < res[i].size(); j++)
		{
			std::cout << res[i][j] << " ";
		}
		std::cout << std::endl;
	}

}
