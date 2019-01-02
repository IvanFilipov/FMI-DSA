/*
 * Traversing a given graph using depth first search (DFS) strategy.
 * Searching for a path from a vertex to another.
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
// visited array
using visited = std::array<bool, MAX_VER_VAL + 1>;
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

// recursively searching for path from current to target
bool dfs_find_rec(vertex current, vertex target, visited& is_visited) {
	// entering in this vertex
	printf("-> %c", current);
	// check if it is the target
	if (current == target)
		return true;
	// mark it as visited
	is_visited[current - 'A'] = true;
	// get iterator for the adjacent list
	graph::iterator it = G.find(current);
	// no such vertex
	if (it == G.end()) {
		putchar('\n');
		return false;
	}
	// if we have a list for this vertex
	// for each of it's adjacent vertices
	for (vertex adj : it->second) {
		// if the adjacent is not visited
		if (!is_visited[adj - 'A']) {
			// go in the adjacent and run the algorithm from there
			if (dfs_find_rec(adj, target, is_visited))
				return true; // if in the recursion we have found the target, return true
			// output that we are going back from an adjacent
			printf("<- %c\n",adj);
		}
	}
	// if we got here there are not path between current and target
	return false;
}

// a wrapper around recursive function
bool dfs_find(vertex start, vertex target) {
	// create visited array
	visited is_visited = { false, };
	// returns the result from the recursive function
	return dfs_find_rec(start, target, is_visited);
}

int main() {
	
	/* fill the graph with some vertices and edges */
	init_graph();
	/* which are the start and target vertices */
	vertex start = 'A';
	vertex target = 'P';
	std::printf("\nsearching for vertex %c from %c using DFS\n\n", target, start);
	
	/* runs the algorithm with start and target */
	if (dfs_find(start, target))
		std::printf("\nfound vertex %c\n", target);
	else
		std::printf("\ncan't find vertex %c\n",target);

	// change the target
	target = 'I';
	std::printf("\n\nsearching for vertex %c from %c using DFS\n\n", target, start);
	
	/* runs the algorithm again */
	if (dfs_find(start, target))
		std::printf("\nfound vertex %c\n", target);
	else
		std::printf("\ncan't find %c\n", target);

	return 0;
}
