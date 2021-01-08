#include <iostream>
#include  "Graphs\Adjacency_list_graph\AdjListGraph.h"
#include  "Graphs\Adjacency_matrix_graph\AdjMatrixGraph.h"
#include  "Graphs\Edge_list_graph\EdgeListGraph.h"
#include  "Graphs\Algorithms\GraphAlgorithms.h"
#include "Graphs\Union-find\Union-find.h"

void MSTtest();
void checkCycleTest();
void topoSortTest();
int main()
{	
	MSTtest();

}
void checkCycleTest()
{
	AdjMatrixGraph g1(7, true);

	g1.addEdge(0, 1);
	g1.addEdge(0, 2);
	g1.addEdge(1, 3);
	g1.addEdge(2, 4);
	g1.addEdge(3, 5);
	g1.addEdge(4, 5);

	std::cout << containsCycle(g1) << std::endl;

	g1.addEdge(5, 2);

	std::cout << containsCycle(g1) << std::endl;
}

void topoSortTest()
{
	AdjListGraph g1(7, true);

	g1.addEdge(0, 1);
	g1.addEdge(0, 2);
	g1.addEdge(1, 3);
	g1.addEdge(2, 4);
	g1.addEdge(3, 5);
	g1.addEdge(4, 5);

	g1.addEdge(6, 0);

	std::vector<int> result;
	TopoSort(g1, result);
	for (int i = 0; i < result.size(); i++)
		std::cout << result[i] << " ";
}
void MSTtest()
{
	EdgeListGraph g1(9, false);

	g1.addEdge(0, 1, 4);
	g1.addEdge(0, 7, 8);
	g1.addEdge(1, 7, 11);
	g1.addEdge(1, 2, 8);
	g1.addEdge(7, 8, 7);
	g1.addEdge(7, 6, 1);
	g1.addEdge(8, 6, 6);
	g1.addEdge(2, 8, 2);
	g1.addEdge(2, 3, 7);
	g1.addEdge(2, 5, 4);
	g1.addEdge(5, 6, 2);
	g1.addEdge(3, 5, 14);
	g1.addEdge(3, 4, 9);
	g1.addEdge(5, 4, 10);

	AdjListGraph MST(g1.getVertexCount(),false);
	std::cout << Kurskal(g1, MST)<<std::endl; //Or PRIM
}