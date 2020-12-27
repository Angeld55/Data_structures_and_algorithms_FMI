#include <iostream>
using namespace std;

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

int main()
{
	
	AdjListGraph g1(6, false);

	g1.addEdge(0, 1);
	g1.addEdge(0, 2);
	g1.addEdge(1, 3);
	g1.addEdge(2, 4);
	g1.addEdge(3, 5);

	DFS(g1, 0);
	std::cout << endl;

	EdgeListGraph g2(5, false);

	g2.addEdge(0, 1);
	g2.addEdge(0, 3);
	g2.addEdge(1, 2);
	g2.addEdge(3, 4);

	BFS(g2, 0);
}