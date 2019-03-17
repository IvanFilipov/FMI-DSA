/*******************************************************************************
 * This file is part of the "Data structures and algorithms" course. FMI 2018/19 
 *******************************************************************************/

/**
 * @file   bfs_general.cpp
 * @author Ivan Filipov
 * @date   01.2019
 * @brief  Simply traversing a graph using breadth first search strategy.
 *
 * @see https://en.wikipedia.org/wiki/Breadth-first_search
 */

#include <cstdio>// std::printf(), std::putchar()
#include <queue> // std::queue
#include <array> // std::array
#include <vector>// std::vector
#include <unordered_map> // std::unordered_map

/// maximum value of each vertex
const unsigned int MAX_VER_VAL = 26;
/// each vertex will be a character
typedef char vertex;
/// using lists of adjacent vertices representation of graph
using graph = std::unordered_map<vertex, std::vector<vertex>>;

/**
 * @brief Creates a graph with some edges.
 * @retval the created graph
 */
graph init_graph() {
	
	graph G;
	G['A'] = { 'B' };
	G['B'] = { 'C', 'D' };
	G['C'] = { 'F', 'H' };
	G['D'] = { 'L' };
	G['F'] = { 'I' };
	G['H'] = { 'I' };
	G['I'] = { 'J' };
	G['J'] = { 'K' };
	G['L'] = { 'H' };
	
	return G;
}

/**
 * @brief Runs BFS algorithm in graph.
 * @param[in] G: input graph
 * @param[in] v_begin: starting from that vertex 
 *
 * @note Time complexity : O((m + n)).
 */
void bfs_traversal(const graph& G, vertex start) {
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
		graph::const_iterator it = G.find(wave.front());
		// not found...
		if (it == G.end()) {
			std::putchar('\n');
			wave.pop();
			continue;
		}
		// if found, it is an iterator to a pair { vertex, adj_list }
		// for each adjacent of the vertex ...
		for (vertex adj: it->second) {
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
	graph G = init_graph();
	
	/* from which vertex to start the algo */
	vertex start = 'A';
	std::printf("\nstarting BFS traversal from vertex \'%c\'\n\n", start);
	
	/* run the algorithm */
	bfs_traversal(G, start);

	return 0;
}
