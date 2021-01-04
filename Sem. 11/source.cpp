#include <iostream>
#include  "Graphs\Adjacency_list_graph\AdjListGraph.h"
#include  "Graphs\Adjacency_matrix_graph\AdjMatrixGraph.h"
#include  "Graphs\Edge_list_graph\EdgeListGraph.h"
#include  "Graphs\Algorithms\GraphAlgorithms.h"


// Алгоритми върху графи.
// Най-къс път в тегловен граф. 
// Dijkstra's algorithm  - графът трябва да има неотрицателни тегла


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
void tests()
{




}
int main()
{
	AdjListGraph g1(9, false);

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

	std::vector<int> path;
	AdjListGraph MST(g1.getVertexCount(),false);
	std::cout << Prim(g1, MST)<<std::endl;


}