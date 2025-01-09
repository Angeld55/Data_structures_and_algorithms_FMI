#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <tuple>
#include <iomanip> 
#include <climits>
#include <algorithm>

class Graph
{
	bool isOriented;
	size_t V;
	std::vector<std::vector<std::pair<int, int>>> adj;

public:
	Graph(size_t V, bool isOriented);
	void addEdge(size_t start, size_t end, int weight);

	size_t dijkstra(size_t start, size_t end, std::vector<size_t>& path) const;

};

Graph::Graph(size_t V, bool isOriented) : adj(V), V(V), isOriented(isOriented)
{}
void Graph::addEdge(size_t start, size_t end, int weight)
{
	adj[start].push_back(std::make_pair(end, weight));
	if (!isOriented)
		adj[end].push_back(std::make_pair(start, weight));
}

size_t Graph::dijkstra(size_t start, size_t end, std::vector<size_t>& path) const
{
	std::vector<size_t> distances(V, INT_MAX);
	std::vector<size_t> prevs(V);


	struct vertexAndDistancePair
	{
		size_t vertex;
		size_t distFromStart;

		bool operator<(const vertexAndDistancePair& other) const
		{
			return distFromStart > other.distFromStart;
		}
	};

	std::priority_queue<vertexAndDistancePair> q;

	distances[start] = 0;

	q.push({ start, 0 });

	while (!q.empty())
	{
		vertexAndDistancePair current = q.top();
		q.pop();
        
		if (current.vertex == end)
		{
		     //get path
			while (end != start)
			{
				path.push_back(end);
				end = prevs[end];
			}
			path.push_back(start);

			std::reverse(path.begin(), path.end());
            //
			return distances[current.vertex];
		}
    
        
        
		for (int i = 0; i < adj[current.vertex].size(); i++)
		{
			size_t currentNeighbor = adj[current.vertex][i].first;

			size_t newDist = current.distFromStart + adj[current.vertex][i].second;
			if (distances[currentNeighbor] > newDist)
			{
				distances[currentNeighbor] = newDist;
				q.push({ currentNeighbor, newDist });
				prevs[currentNeighbor] = current.vertex;
			}
		}

	}
	return INT_MAX;

}

int main()
{
	Graph g(9, false);
	g.addEdge(0, 1, 4);
	g.addEdge(0, 7, 8);
	g.addEdge(1, 7, 11);
	g.addEdge(1, 2, 8);
	g.addEdge(7, 8, 7);
	g.addEdge(7, 6, 1);
	g.addEdge(8, 6, 6);
	g.addEdge(8, 2, 2);
	g.addEdge(2, 5, 4);
	g.addEdge(6, 5, 2);
	g.addEdge(2, 3, 7);
	g.addEdge(3, 5, 14);
	g.addEdge(3, 4, 9);
	g.addEdge(5, 4, 10);

	{ //Dijkstra example
		std::vector<size_t> path;
		std::cout << "Shortest weight path from 0 to 4(with Dijkstra):" << g.dijkstra(0, 4, path) << std::endl;
		std::cout << "Path : ";
		for (int i = 0; i < path.size(); i++)
			std::cout << path[i] << " ";
		std::cout << std::endl << std::endl << std::endl;
	}


}
