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
void AdjMatrixGraph::removeVertex(int vertex_index)
{
	if (!existsVertex(vertex_index))
		throw "Invalid vertex!";
	int vector_index = vertex_index - 1;
	adjMatrix.erase(adjMatrix.begin() + vector_index);
	for (auto it = adjMatrix.begin(); it < adjMatrix.end(); it++)
		it->erase(it->begin() + vector_index);
	vertexCount--;
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
