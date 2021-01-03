#ifndef _GRAPH_ALGORITHMS_
#define _GRAPH_ALGORITHMS_

#include "..\Graph.h"
#include <queue>
#include <stack>
#include <functional>

void BFS(const Graph& g, int start, std::vector<int>& order);
void DFS(const Graph& g, int start, std::vector<int>& order);
bool isConnected(const Graph& g);
bool containsPath(const Graph& g, int start, int end);

#endif