#include "..\Graph.h"
#include <list>
class EdgeListGraph : public Graph
{
	struct Edge
	{
		int start;
		int end;
		int weight;
	};
	std::list<Edge> edges;
public:
	EdgeListGraph(int n, bool oriented);
	int addVertex(); //return the index of the new vertex
	void removeVertex(int vertex_index);
	void addEdge(int start, int end, int weight = 1);
	void removeEdge(int start, int end);

	void getSuccessors(int vertex, std::vector<std::pair<int, int>>& vertexAdj) const;
};
