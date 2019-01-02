/*
 * Creating minimal spanning tree from a graph, using Kruskal's algorithm.
 * This file is part of the "Data structures and algorithms" course. FMI 2018/19
 *
 * Author : Ivan Filipov	
 */

#include <cstdio> // std::printf
#include <list>   // std::list
#include <tuple>  // std::tuple
#include <array>  // std::array

using std::printf;

const int MAX_VER_VAL = 26;
// mark for unknown vertex's parent
const char NO_PARENT = '?';
// vertices are characters
typedef char vertex;
// weights are numbers
typedef unsigned int weight;
// each edge is a tuple - vertex : vertex : weight
using edge = std::tuple<vertex, vertex, weight>;
// the graph is represented as a list of edges
using graph = std::list<edge>;
// a map for vertex -> its parent
using parent_list = std::array<vertex, MAX_VER_VAL + 1>;

// fills the graph with some edges
graph init_graph() {
	
	return {
		std::make_tuple('A', 'B', 1),
		std::make_tuple('A', 'D', 2),
		std::make_tuple('B', 'C', 3),
		std::make_tuple('B', 'E', 13),
		std::make_tuple('C', 'D', 4),
		std::make_tuple('C', 'F', 3),
		std::make_tuple('D', 'F', 16),
		std::make_tuple('D', 'H', 14),
		std::make_tuple('E', 'F', 12),
		std::make_tuple('E', 'I', 13),
		std::make_tuple('E', 'J', 1),
		std::make_tuple('F', 'H', 1),
		std::make_tuple('H', 'I', 1)
	};
}

// simply output a graphs contain
void print_graph(const graph& G) {
	
	for (const edge& e : G)
		printf("(%c, %c, %u) ", std::get<0>(e),
				std::get<1>(e), std::get<2>(e));
	printf("\n\n");
}

// compares two edges by their weight
bool edge_cmp(const edge& e1, const edge& e2) {

	return (std::get<2>(e1) < std::get<2>(e2));
}

// gets an index of vertex and returns it's 
// root from the set it belongs to
size_t find_root(size_t index, const parent_list& pl) {
	// until the current index is not root
	// go to it's father
	while (pl[index] != NO_PARENT)
		index = pl[index];

	return index;
}

graph build_kruskal_mst(graph& G) {
	// the result minimal spanning tree
	graph mst;
	// list of parents for each vertex
	parent_list pl;
	// initialize all in different subsets
	pl.fill(NO_PARENT);
	// we can calculate the weight of the MST
	unsigned int mst_w = 0;
	// sorting all edges depending on their weights
	G.sort(edge_cmp);
	// roots indexes
	size_t r1, r2;
	// for each edge from the sorted list
	for (const edge& e : G) {
		// the sub-set's root in which vertexes are
		r1 = find_root(std::get<0>(e) - 'A', pl);
		r2 = find_root(std::get<1>(e) - 'A', pl);
		// if they are not in the same subset
		if (r1 != r2) {
			// add the edge into the result set
			mst.push_back(e);
			// add the weight of this edge to total
			mst_w += std::get<2>(e);
			//join the two subsets
			pl[r2] = r1;
		}
	}
	
	printf("Minimal spanning tree's weight : %u\n", mst_w);
	return mst;
}


int main() {
	
	/* fill the graph with some vertices and edges */
	graph G = init_graph();
	
	printf("\nthe given graph contains:\n");
	print_graph(G);
	
	/* run the algorithm */
	graph mst = build_kruskal_mst(G);
	printf("\nthe result MST contains:\n");
	print_graph(mst);

	return 0;
}
