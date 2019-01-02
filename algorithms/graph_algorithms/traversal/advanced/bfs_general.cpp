/*
 * Traversing a given graph using breadth first search (BFS) strategy.
 * This file is part of the "Data structures and algorithms" course. FMI 2018/19
 *
 * Author : Ivan Filipov	
 */

#include <cstdio>// std::printf(), std::putchar()
#include <queue> // std::queue
#include <array> // std::array
#include <vector>// std::vector
#include <unordered_map> // std::unordered_map

// constant for the size of visited array
const unsigned int MAX_VER_VAL = 26;
// each vertex will be a character
typedef char vertex;
// using lists of adjacent vertices representation of graph
using graph = std::unordered_map<vertex, std::vector<vertex>>;
// creates a graph object
graph G;

// initialize the graph vertices and edges
void init_graph() {

	G['A'] = { 'B' };
	G['B'] = { 'C', 'D' };
	G['C'] = { 'F', 'H' };
	G['D'] = { 'L' };
	G['F'] = { 'I' };
	G['H'] = { 'I' };
	G['I'] = { 'J' };
	G['J'] = { 'K' };
	G['L'] = { 'H' };
}
// runs BFS from starting point "start" into graph G
void bfs_traversal(vertex start) {
	// which are visited
	std::array<bool, MAX_VER_VAL + 1> is_visited = { false, };
	// the wave of the algorithm
	std::queue<vertex> wave;
	// adding the start vertex
	wave.push(start);
	// until the wave is not empty
	while (!wave.empty()) {
		printf("from %c : ", wave.front());
		// trying to get the adjacent list of this vertex
		graph::iterator it = G.find(wave.front());
		// not found...
		if (it == G.end()) {
			std::putchar('\n');
			wave.pop();
			continue;
		}
		// if found, it is an iterator to a pair { vertex, adj_list }
		// for each adjacent of the vertex ...
		for (vertex adj : it->second) {
			// if not visited
			if (!is_visited[adj - 'A']) {
			// mark it as visited
				printf("%c ", adj);
				is_visited[adj - 'A'] = true;
			// add it to the wave
				wave.push(adj);
			}
		}
		putchar('\n');
		// remove the front of the wave
		wave.pop();
	}
	// end of algorithm
	std::printf("traverse completed!\n");
}


int main() {
	
	/* fill the graph with some vertices and edges */
	init_graph();
	/* from which vertex to start the algo */
	vertex start = 'A';
	std::printf("\nstarting BFS traversal from vertex \'%c\'\n\n", start);
	/* run the algorithm */
	bfs_traversal(start);

	return 0;
}
