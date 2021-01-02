#include "..\Graph.h"

class AdjMatrixGraph : public Graph
{
	std::vector<std::vector<int>> adjMatrix;
public:
	AdjMatrixGraph(int n, bool oriented);

	int addVertex();
	void removeVertex(int vertex_index);
	void addEdge(int start, int end, int weight = 1);
	void removeEdge(int start, int end);

	void getSuccessors(int vertex, std::vector<std::pair<int, int>>& vertexAdj) const;

};
