#include <iostream>
#include <vector>
#include <queue>
using namespace std;


class Graph
{
	std::vector<std::vector<int>> adjList;

public:
	Graph(int V) : adjList(V) {}
	void addEdge(int start, int end)
	{
		adjList[start].push_back(end);
		adjList[end].push_back(start);
	}
	void BFS(int start, vector<bool>& visited, int& sum, int& vertexCount);
	double getAverageOfConnectedComponents();
	
};
void Graph::BFS(int start, vector<bool>& visited, int& sum, int& vertexCount)
{
	queue<int> q;
	q.push(start);
	visited[start] = true;

	while (!q.empty())
	{
		int currentVertex = q.front();
		q.pop();

		sum += currentVertex;
		vertexCount++;

		for (int i = 0; i < adjList[currentVertex].size(); i++)
		{
			if (visited[adjList[currentVertex][i]])
				continue;
			visited[adjList[currentVertex][i]] = true;
			q.push(adjList[currentVertex][i]);
		}
	}

}
double Graph::getAverageOfConnectedComponents()
{
	vector<bool> visited(adjList.size(), false);

	double result = 0;
	for (int i = 0; i < adjList.size(); i++)
	{
		if (!visited[i])
		{
			int vertexCount = 0, sum = 0;
			BFS(i, visited, sum, vertexCount);
			result +=  ((double)sum / vertexCount);
		}
	}
	return result;

}

int main()
{
	Graph g(9);
	g.addEdge(7, 8);

	g.addEdge(4, 5);
	g.addEdge(4, 6);
	g.addEdge(6, 5);

	g.addEdge(2, 1);
	g.addEdge(2, 3);
	g.addEdge(1, 0);
	g.addEdge(0, 3);

	cout << g.getAverageOfConnectedComponents();
}
