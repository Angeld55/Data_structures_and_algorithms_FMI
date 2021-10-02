#ifndef _GRAPH_ALGORITHMS_
#define _GRAPH_ALGORITHMS_

#include "../Graph.h"
#include "../Edge_list_graph/EdgeListGraph.h"
#include <queue>
#include <stack>
#include <functional>

void BFS(const Graph& g, int start, std::vector<int>& order);
void DFS(const Graph& g, int start, std::vector<int>& order);
bool isConnected(const Graph& g);
bool containsPath(const Graph& g, int start, int end);
int Dijkstra(const Graph& g, int start, int end, std::vector<int>& path);

int Prim(const Graph& g, Graph& MST);
int Kurskal(const Graph& g, Graph& MST);

bool containsCycle(const Graph& g);

void TopoSort(const Graph& g, std::vector<int>& result);
#endif