#include "..\Graph.h"


//sparse matrix // разредени матрици
class AdjMatrixGraph : public Graph
{
	std::vector<std::vector<int>> adjMatrix;
public:
	AdjMatrixGraph(int n, bool oriented);

	int addVertex();

	void addEdge(int start, int end, int weight = 1);
	void removeEdge(int start, int end);

	void getNeighbours(int vertex, std::vector<std::pair<int, int>>& vertexAdj);

};
AdjMatrixGraph::AdjMatrixGraph(int n, bool oriented) : Graph(n, oriented), adjMatrix(n)
{
	std::vector<int> templateVector(n);
	for (int i = 0; i < n; i++)
		adjMatrix[i] = templateVector;
}
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
void AdjMatrixGraph::getNeighbours(int vertex, std::vector<std::pair<int, int>>& adj) // O(n)
{
	if (!existsVertex(vertex))
		throw "Invalid vertex!";

	for (int i = 0; i < adjMatrix[vertex].size(); i++)
	{
		if (adjMatrix[vertex][i] > 0)
			adj.push_back(std::make_pair(i,adjMatrix[vertex][i]));
	}
}
