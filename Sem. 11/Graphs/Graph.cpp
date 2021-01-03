#include "Graph.h"

bool Graph::existsVertex(int vertex) const
{
	return vertex < vertexCount && vertex > 0;
}
int Graph::getVertexCount() const
{
	return vertexCount;
}
