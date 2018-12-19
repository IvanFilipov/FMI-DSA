/*
 * Finding the shortest path from starting vertex to all others, using Dijkstra's algorithm.
 * This file is part of the "Data structures and algorithms" course. FMI 2018/19
 *
 * Author : Ivan Filipov	
 */

#include <cstdio> // std::printf()
#include <array>  // std::array
#include <vector> // std::vector
#include <queue>  // std::priority_queue
#include <limits> // std::numeric_limits
#include <unordered_map> // std::unordered_map

// all possible values for vertices
const unsigned int MAX_VER_VAL = 26;
// mark for unknown vertex's parent
const char NO_PARENT = '?';
// mark for unreachable vertex
const unsigned int MAX_DISTANCE = std::numeric_limits<unsigned int>::max();
// vertices are characters
typedef char vertex;
//!< weights are natural numbers
typedef unsigned int weight;
// each edge is a pair - vertex (to) : weight
using edge  = std::pair<vertex, weight>;
// the graph is represented as a lists of adjacent for each vertex
using graph = std::unordered_map<vertex, std::vector<edge>>;
// parent list contains at index i, which is the parent of vertex i
using parent_list     = std::array<vertex, MAX_VER_VAL + 1>;
// distance vector contains at index i, what is the distance to it
using distance_vector = std::array<weight, MAX_VER_VAL + 1>;

// creates a graph with some edges
graph init_graph() {
	
	graph G;
	G['A'] = { {'B', 5}, {'F', 8} };
	G['B'] = { {'C', 4}, {'D', 1} };
	G['C'] = { {'F', 9}, {'H', 23} };
	G['D'] = { {'E', 3} };
	G['E'] = { {'H', 6}, {'A', 18} };
	G['F'] = { {'G', 5}, {'J', 6} };
	G['G'] = { {'I', 3} };
	G['H'] = { {'I', 11} };
	G['I'] = { {'J', 2} };
	G['J'] = { {'E', 15} };
	
	return G;
}

// recursively prints the path from @v_start, to @v_end, using the
// parent list @pl
void print_path_rec(vertex v_start, vertex v_end, const parent_list& pl) {
	// until we reach the starting vertex
	if (pl[v_end - 'A'] != v_start) {
		// recursively print the path with one step backwards
		print_path_rec(v_start, pl[v_end - 'A'], pl);
	}
	// actual printing after returning from the recursion
	std::printf("->%c", v_end);
}

// prints the info about all paths in a graph
// from starting vertex @v_begin, after
// running Dijkstra's algorithm with output in
// parent list @pl and distance_vector @dv
void print_paths_info(vertex v_begin, const parent_list& pl, const distance_vector& dv) {
	// for each vertex
	for (size_t i = 0; i < dv.size() - 1; i++) {
		std::printf("path between %c and %c :", v_begin, 'A' + i);
		// check if there is a path
		if (dv[i] == MAX_DISTANCE)
			std::printf("no such path!\n");
		else {
			// print the starting vertex
			std::printf(" %c", v_begin);
			// print all other vertices on the path
			if (pl[i] != NO_PARENT)
				print_path_rec(v_begin, i + 'A', pl);
			// print info about the distance
			std::printf("\ndistance : %u \n\n", dv[i]);
		}
	}	
}

// compares two edges @e1 and @e2 by their weight
auto edge_cmp = [](const edge& e1, const edge& e2) -> bool {

	return e1.second > e2.second;
};

// runs Dijkstra's algorithm in graph @G,
// starting from vertex               @v_begin
// writes parent for each vertex in   @pl
// writes distance to each vertex in  @dv
void dijkstra_shortest_paths(graph& G, vertex v_begin, parent_list& pl, distance_vector& dv) {
	// mark each vertex's parent as unknown
	pl.fill(NO_PARENT);
	// mark distance to each vertex as unreachable
	dv.fill(MAX_DISTANCE);
	// mark distance to starting vertex: 0
	dv[v_begin - 'A'] = 0;
	// all vertices we have complete our job with
	std::array<bool, MAX_VER_VAL + 1> done = { false, };
	// a priority queue for
	// all the vertexes we can see at a moment,
	// sorted by the cost of the shortest known path to them
	std::priority_queue<
		edge,               // elements:   vertex - current path cost
		std::vector<edge>,  // allocator:  use std::vector as underlaying data structure
		decltype(edge_cmp)> // comparator: use the lambda function "edge_cmp"
		wave(edge_cmp);     // pass the comparator as constructor's argument
	// adding the starting vertex into the queue
	wave.push(std::make_pair(v_begin, dv[v_begin - 'A']));	
	// until the queue is not empty
	while (!wave.empty()) {
		// taking the best 
		edge cur = wave.top();
		wave.pop();
		// we are done with this vertex
		done[cur.first - 'A'] = true;
		// get it's adjacency list 
		graph::iterator it = G.find(cur.first);
		// this vertex has no adjacent vertex
		if (it == G.end())
			continue;
		// for each edge starting from the current vertex
		for (const edge & adj : it->second) {
			// if we are not done with this child
			if (!done[adj.first - 'A']) {
				// trying to optimize
				// the current path cost                
				if (dv[adj.first - 'A'] >               // the best known before
					dv[cur.first - 'A'] + adj.second) { // the best to current + the edge between them
					// mark the parent
					pl[adj.first - 'A'] = cur.first;
					// optimize the distance
					dv[adj.first - 'A'] = dv[cur.first - 'A'] + adj.second;
					// add the current edge into the queue
					wave.push(std::make_pair(adj.first, dv[adj.first - 'A']));
				}
			}
		}
	}
}

int main() {
	
	/* fill the graph with some vertices and edges */
	graph G = init_graph();
	/* create parent list and distance vector */
	parent_list pl;
	distance_vector dv;
	
	/* run the algorithm */
	vertex v_begin = 'A';
	dijkstra_shortest_paths(G, v_begin, pl, dv);
	
	/* print the info about all paths */
	print_paths_info(v_begin, pl, dv);
	
	return 0;
}
