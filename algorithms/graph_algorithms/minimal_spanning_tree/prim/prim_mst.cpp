/*******************************************************************************
 * This file is part of the "Data structures and algorithms" course. FMI 2018/19 
 *******************************************************************************/

/**
 * @file   prim_mst.cpp
 * @author Nikolay Babulkov
 * @author Ivan Filipov
 * @date   01.2019
 * @brief  Creating minimal spanning tree from a graph, using Prim's algorithm.
 *
 * @see https://en.wikipedia.org/wiki/Prim%27s_algorithm
 */

#include <cstdio> // std::printf()
#include <vector> // std::vector
#include <queue>  // std::priority queue
#include <tuple>  // std::tuple, std::get()
#include <unordered_map> // std::unordered_map
#include <unordered_set> // std::unordered_set
#include <limits>        // std::numeric_limits

using std::printf;

/// vertices are characters
typedef char vertex;
/// weights are numbers
typedef int weight;
/// each edge is a tuple s_vertex : e_vertex : weight
using edge = std::tuple<vertex, vertex, weight>; 
/// for each vertex we will have a list of it's edges to children
using children_list = std::vector<edge>;
/// the graph is represented as a lists of adjacent for each vertex
using graph = std::unordered_map<vertex, children_list>;

/**
 * @brief Creates a graph with some edges.
 * @retval the created graph
 */
graph init_graph() {
	
	edge a2b('a', 'b' ,9),
		 a2c('a', 'c', 3),
		 a2d('a', 'd', 5),
		 b2e('b', 'e', 1),
		 c2b('c', 'b', 2),
		 c2d('c', 'd', 1),
		 d2e('d', 'e', 7),
		 e2a('e', 'a', 1),
		 e2c('e', 'c', 6);
		
	graph g;
	g['a'] = { a2b, a2c, a2d };
	g['b'] = { b2e };
	g['c'] = { c2b, c2d };
	g['d'] = { d2e };	
	g['e'] = { e2a, e2c };	
	return g; 
}

/**
 * @brief simply output a graphs contain
 * @param[in] G: graph to be outputted
 */
void print_graph(const graph& G) {
	
	for (const std::pair<vertex, children_list>& v_child : G) {
		printf("from '%c' to : { ", v_child.first);
		for (const edge& e: v_child.second)
			printf("(%c, %d) ", std::get<1>(e), std::get<2>(e));
		printf("}\n");
	}
		
	printf("\n\n");
}

/**
 * @brief Checks if a given vertex is already in the MST.
 * @param[in] v: vertex to be checked 
 * @param[in] m: current MST
 * @retval true if the vertex is in the MST.
 */
bool is_in_mst(const vertex& v, const std::unordered_set<vertex>& m) {
	
	return m.find(v) != m.end(); 
}

/**
 * @brief Gets current smallest weight cost to vertex.
 * @param[in] v: vertex to be checked 
 * @param[in] cost: current known costs
 * @retval current best known weight
 *
 * @note if the vertex is not visited, returns INT_MAX (c++ equivalent of +infinity).
 */
weight get_weight(const vertex& v, const std::unordered_map<vertex, weight>& cost) {
	
	if (cost.find(v) == cost.end()) 
		return std::numeric_limits<int>::max();
	else
		return cost.find(v)->second;
}

/**
 * @brief compares two edges by their weight
 * @param[in] e1: lhs edge
 * @param[in] e2: rhs edge
 * @retval true if e1 is heavier than e2
 */
auto edge_cmp = [](const edge& e1, const edge& e2) {

	return (std::get<2>(e1) > std::get<2>(e2));
};

/**
 * @brief Creates an minimal spanning tree for a graph.
 * @param[in] G: input graph
 * @param[in] v_begin: starting vertex
 * @retval the MST for that graph
 */ 
// uses v_begin as starting vertex
graph build_prim_mst(const graph& G, vertex v_begin) {
	// the result
	graph mst;
	// a set containing all vertices already added into the MST
	std::unordered_set<vertex> done;
	// a map storing the smallest weight to given vertex.
	std::unordered_map<vertex, weight> cur_best_costs;
	// a priority queue used for the natural order of edges(pairs).
	// first pop the edges with less weight.
	// we have a queue of edges as adapter over vector of edges, using edge_cmp as compare function
	std::priority_queue<edge, std::vector<edge>, decltype(edge_cmp)> q(edge_cmp);
	// create a beginning edge
	edge start(v_begin, v_begin, 0);
	// add it to the queue
	q.push(start);
	// until the queue is not empty
	while (!q.empty()) {
		// get the cheapest edge
		edge cur_edge = q.top(); q.pop();
		vertex cur_v = std::get<1>(cur_edge);
		vertex parent_v = std::get<0>(cur_edge);
		// add the vertex into the set with visited vertices
		if (done.insert(cur_v).second) {
			// if successfully added (seen for first time)
			// add it to the result graph
			if (!(cur_v == v_begin && parent_v == v_begin)) // do not add v_begin, v_begin, 0
				mst[parent_v].push_back(cur_edge);
		}
		// iterating over the children_list of the current vertex
		const children_list& adj = G.find(cur_v)->second;
		for (const edge& e: adj) {
			// get the vertex and edge's cost
			vertex child = std::get<1>(e);
			weight w     = std::get<2>(e);
			// get current best weight for child or +inf if not visited
			weight weight_current = get_weight(child, cur_best_costs);
			// add it to the MST if the cost is better than the currently known best
			if (!is_in_mst(child, done) && (weight_current > w)) {
				cur_best_costs[child] = w; // update current best cost
				q.push(e);                 // add the edge to the queue
			}
		}
	}
	// return the result MST
	return mst;
}

int main() {
	
	/* fill the graph with some vertices and edges */
	graph G = init_graph();
	printf("\nthe given graph contains:\n");
	print_graph(G);
	
	/* run the algorithm */
	vertex v_begin = 'a';
	graph mst = build_prim_mst(G, v_begin);
	
	printf("\nbuilding MST from %c:\n", v_begin);
	print_graph(mst);

	return 0;
}
