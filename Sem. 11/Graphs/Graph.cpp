#pragma once
#include "Graph.h"

bool Graph::existsVertex(int vertex) const
{
	return vertex < vertexCount;
}
int Graph::getVertexCount() const
{
	return vertexCount;
}
