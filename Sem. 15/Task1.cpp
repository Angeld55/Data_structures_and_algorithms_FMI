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
	}
	void getSumEvenSumOdd(int start, int& sumEven, int& sumOdd)
	{//BFS
		queue<pair<int, bool>> q;
		// <vertex, isDistanceFromStartEven>

		vector<bool> visited(adjList.size(), false);
		q.push(make_pair(start, true));

		visited[start] = true;

		while (!q.empty())
		{
			pair<int, bool> currentVertex = q.front();
			q.pop();
			if (currentVertex.second)
				sumEven += currentVertex.first;
			else
				sumOdd += currentVertex.first;

			for (int i = 0; i < adjList[currentVertex.first].size(); i++)
			{
				int neighbor = adjList[currentVertex.first][i];
				if (visited[neighbor])
					continue;
				q.push(make_pair(neighbor, !currentVertex.second));
				visited[neighbor] = true;
			}

		}
	}

};

int main()
{
	int n;
	cin >> n;
	Graph g(n);
	int m;
	cin >> m;
	
	for (int i = 0; i < m; i++)
	{
		int start, end;
		cin >> start >> end;
		g.addEdge(start, end);
	}

	int start;
	cin >> start;

	int sumEven = 0, sumOdd = 0;
	g.getSumEvenSumOdd(start, sumEven, sumOdd);
	cout << "Result: Even: " << sumEven << ", Odd:" << sumOdd << endl;
}
