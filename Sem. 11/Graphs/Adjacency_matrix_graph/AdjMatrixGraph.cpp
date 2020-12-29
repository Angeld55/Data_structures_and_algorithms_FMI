#include "GraphAlgorithms.h"
#include "AdjMatrixGraph.h"

AdjMatrixGraph::AdjMatrixGraph(int n, bool oriented) : Graph(n, oriented), adjMatrix(n, std::vector<int>(n))
{}

int AdjMatrixGraph::addVertex() // O(n)
{
	adjMatrix.push_back(std::vector<int>(adjMatrix.size() + 1));
	for (int i = 0; i < adjMatrix.size() - 1; i++)
		adjMatrix[i].push_back(0);
	vertexCount++;
	return adjMatrix.size() - 1;
}
void AdjMatrixGraph::addEdge(int start, int end, int weight) // O(1)
{
	if (!existsVertex(start) || !existsVertex(end))
		throw "Invalid vertices!";

	if (adjMatrix[start][end] != 0)
		throw "Such edge exists!";

	adjMatrix[start][end] = weight; 
	if (!oriented)
		adjMatrix[end][start] = weight;
}
void AdjMatrixGraph::removeEdge(int start, int end) // O(1)
{
	if (!existsVertex(start) || !existsVertex(end))
		throw "Invalid vertices!";

	adjMatrix[start][end] = 0;
	if (!oriented)
		adjMatrix[end][start] = 0;
}
void AdjMatrixGraph::getSuccessors(int vertex, std::vector<std::pair<int, int>>& adj) const // O(n)
{
	if (!existsVertex(vertex))
		throw "Invalid vertex!";

	for (int i = 0; i < adjMatrix[vertex].size(); i++)
	{
		if (adjMatrix[vertex][i] > 0)
			adj.push_back(std::make_pair(i,adjMatrix[vertex][i]));
	}
}
void AdjMatrixGraph::getPredeccessors(int vertex, std::vector<std::pair<int, int>>& adj) const
{
	if (!existsVertex(vertex))
		throw "Invalid vertex!";

	for (int i = 0; i < adjMatrix[vertex].size(); i++)
	{
		if (adjMatrix[i][vertex] > 0)
			adj.push_back(std::make_pair(i, adjMatrix[i][vertex]));
	}
}

bool AdjMatrixGraph::adjacent(int start, int end) const
{
	if (!existsVertex(start) || !existsVertex(end))
		throw "Invalid vertex!";

	return adjMatrix[start][end];
}

bool AdjMatrixGraph::isConnected() const
{
	std::vector<bool> visited(vertexCount);
	BFS(*this, 0, visited);

	for (int i = 0; i < vertexCount; i++)
	{
		if (visited[i] == 0)
			return false;
	}
	return true;
}

bool AdjMatrixGraph::containsPath(int start, int end) const
{
	if (!existsVertex(start) || !existsVertex(end))
		throw "Invalid vertex!";

	std::vector<bool> visited(vertexCount);
	BFS(*this, start, visited);

	return visited[start] && visited[end];
}