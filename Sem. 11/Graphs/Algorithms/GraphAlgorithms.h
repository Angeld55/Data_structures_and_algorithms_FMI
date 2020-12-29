#ifndef _GRAPH_ALGORITHMS_
#define _GRAPH_ALGORITHMS_

#include "..\Graph.h"
#include <queue>
#include <stack>
#include <functional>

void BFS(const Graph& g, int start, std::vector<bool>& visited);
void DFS(const Graph& g, int start, std::vector<bool>& visited);

#endif