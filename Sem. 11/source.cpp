#include <iostream>
#include  "Graphs\Adjacency_list_graph\AdjListGraph.h"
#include  "Graphs\Adjacency_matrix_graph\AdjMatrixGraph.h"
#include  "Graphs\Edge_list_graph\EdgeListGraph.h"
#include  "Graphs\Algorithms\GraphAlgorithms.h"

//		 0
//	   1   2
//    3    4 
//   5
//

//     0
//  1     3
// 2      4
//

template <typename T>
void printVector(std::vector<T> v)
{
	for (int i = 0; i < v.size(); i++)
		std::cout << v[i] << ' ';
	std::cout << std::endl;
}

int main()
{
	AdjListGraph g1(6, false);

	g1.addEdge(0, 1);
	g1.addEdge(0, 2);
	g1.addEdge(1, 3);
	g1.addEdge(2, 4);
	g1.addEdge(3, 5);

	std::vector<int> orderDFS;
	DFS(g1, 0, orderDFS);
	std::cout << "DFS: ";
	printVector(orderDFS);

	EdgeListGraph g2(5, false);

	g2.addEdge(0, 1);
	g2.addEdge(0, 3);
	g2.addEdge(1, 2);
	g2.addEdge(3, 4);

	std::vector<int> orderBFS;
	BFS(g2, 0, orderBFS);
	std::cout << "BFS: ";
	printVector(orderBFS);

	AdjListGraph t(6, 1);
	t.addEdge(0, 1);
	t.addEdge(1, 2);
	t.addEdge(1, 3);
	t.addEdge(5, 5);
	t.addEdge(5, 4);
	t.addEdge(2, 4);
	t.addEdge(3, 5);
	t.addEdge(4, 5);
	t.addEdge(5, 1);

	int vertex = 5;
	std::vector<std::pair<int, int>> succ;
	t.getSuccessors(vertex, succ);

	std::cout << "Successors vertex 5 AdjListGraph: ";
	for (int i = 0; i < succ.size(); i++)
		std::cout << succ[i].first << ' ';
	
	std::vector<std::pair<int, int>> pred;
	t.getPredeccessors(vertex, pred);

	std::cout << std::endl << "Predeccessors vertex 5 AdjListGraph: ";
	for (int i = 0; i < pred.size(); i++)
		std::cout << pred[i].first << ' ';

	EdgeListGraph g(6, 1);
	g.addEdge(0, 1);
	g.addEdge(1, 2);
	g.addEdge(1, 3);
	g.addEdge(5, 5);
	g.addEdge(5, 4);
	g.addEdge(2, 4);
	g.addEdge(3, 5);
	g.addEdge(4, 5);
	g.addEdge(5, 1);

	std::vector<std::pair<int, int>> succ1;
	t.getSuccessors(vertex, succ1);

	std::cout << std::endl << "Successors vertex 5 EdgeListGraph: ";
	for (int i = 0; i < succ1.size(); i++)
		std::cout << succ1[i].first << ' ';

	std::vector<std::pair<int, int>> pred1;
	t.getPredeccessors(vertex, pred1);

	std::cout << std::endl << "Predeccessors vertex 5 EdgeListGraph: ";
	for (int i = 0; i < pred1.size(); i++)
		std::cout << pred1[i].first << ' ';

	AdjMatrixGraph h(6, 1);
	h.addEdge(0, 1);
	h.addEdge(1, 2);
	h.addEdge(1, 3);
	h.addEdge(5, 5);
	h.addEdge(5, 4);
	h.addEdge(2, 4);
	h.addEdge(3, 5);
	h.addEdge(4, 5);
	h.addEdge(5, 1);

	std::vector<std::pair<int, int>> succ2;
	h.getSuccessors(vertex, succ2);

	std::cout << std::endl << "Successors vertex 5 AdjMatrixGraph: ";
	for (int i = 0; i < succ2.size(); i++)
		std::cout << succ2[i].first << ' ';

	std::vector<std::pair<int, int>> pred2;
	h.getPredeccessors(vertex, pred2);

	std::cout << std::endl << "Predeccessors vertex 5 AdjMatrixGraph: ";
	for (int i = 0; i < pred2.size(); i++)
		std::cout << pred2[i].first << ' ';

	std::cout << std::endl << "Adjacent 1, 3: ";
	std::cout << t.adjacent(1, 3);
	std::cout << g.adjacent(1, 3);
	std::cout << h.adjacent(1, 3);

	std::cout << std::endl << "Adjacent 1, 4: ";
	std::cout << t.adjacent(1, 4);
	std::cout << g.adjacent(1, 4);
	std::cout << h.adjacent(1, 4);

	std::cout << std::endl << "Adjacent 1, 5: ";
	std::cout << t.adjacent(1, 5);
	std::cout << g.adjacent(1, 5);
	std::cout << h.adjacent(1, 5);

	std::cout << std::endl << "Adjacent 5, 1: ";
	std::cout << t.adjacent(5, 1);
	std::cout << g.adjacent(5, 1);
	std::cout << h.adjacent(5, 1);

	std::cout << std::endl << "Adjacent 2, 5: ";
	std::cout << t.adjacent(2, 5);
	std::cout << g.adjacent(2, 5);
	std::cout << h.adjacent(2, 5);

	std::cout << std::endl << "Contains path 1, 3: ";
	std::cout << containsPath(t, 1, 3);
	std::cout << containsPath(g, 1, 3);
	std::cout << containsPath(h, 1, 3);

	std::cout << std::endl << "Contains path 1, 4: ";
	std::cout << containsPath(t, 1, 4);
	std::cout << containsPath(g, 1, 4);
	std::cout << containsPath(h, 1, 4);

	std::cout << std::endl << "Connected: ";
	std::cout << isConnected(t);
	std::cout << isConnected(g);
	std::cout << isConnected(h);
	std::cout << std::endl;

	std::vector<int> bfs;
	BFS(t, 0, bfs);
	std::cout << "BFS: ";
	printVector(bfs);

	std::vector<int> dfs;
	DFS(g, 0, dfs);
	std::cout << "DFS: ";
	printVector(dfs);

}