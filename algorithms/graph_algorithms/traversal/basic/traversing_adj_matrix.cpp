/*
* A basic example of breadth-first-search(bfs) using queue, 
* depth-first-search using stack (iterative), depth-first-search using simple recursion (dfs)
* The graph is represented by adjacent matrix
* This file is part of the "Data structures and algorithms" course. FMI 2018/19
*
* Author : Vasilena Peycheva and Ivan Filipov
*/
#include <iostream> // std::cout, std::endl
#include <queue>    // std::queue
#include <stack>    // std::stack

const int max = 10;

/**
* the graph is represented using
* adjacency matrix
*/
int adj_matrix[max][max] = { {0,}, };

/** mark two vertices as connected */
void add_edge(int i, int j) {

	adj_matrix[i][j] = 1;
	adj_matrix[j][i] = 1;
}

/** initializing the graph with some edges */
void init_graph() {
	
	add_edge(1, 3);
	add_edge(1, 2);
	add_edge(1, 5);
	add_edge(2, 4);
	add_edge(3, 6);
	add_edge(4, 5);
	add_edge(5, 6);
}

/** simply outputs the graph's contain in a nice table */
void print_graph() {
	
	std::cout << "\nthe given graph looks like:" << std::endl;
	
	std::cout << "\nvertex from:    ";
	for (size_t i = 1; i < max; i++)
		std::cout << i << ' ';
	std::cout << std::endl;
	std::cout << "       \\\\\\\\\\    " ; 
	for (size_t i = 1; i < max; i++)
		std::cout << "- ";
	std::cout << std::endl;
	std::cout << "         to: ";
	
	std::cout << 1 << " |";
	for (size_t i = 1; i < max; i++)
		std::cout << adj_matrix[1][i] << ' ';
	std::cout << '|' << std::endl;
		
	for (size_t i = 2; i < max; i++) {
		std::cout << "             " << i << " |";
		for (size_t j = 1; j < max; j++) {
			std::cout << adj_matrix[i][j] << ' ';
		}
		std::cout << '|' << std::endl;
	}
	
	std::cout << "               ";
	for (size_t i = 1; i < max; i++)
		std::cout << "- ";
	std::cout << std::endl << std::endl;
}

/**
* each time we hit unvisited successor of the current vertex,
* we push it to the queue, mark it as visited* and print it on the standard output
* *visited are all vertices that are already visited or are in the queue and will be visited
* the algorithm terminates when there are no elements left in the queue
*/
void bfs(int vertex) {
	
	bool visited[max] = { false, }; // used to mark vertices as visited
	std::queue<int> to_be_visited;  // a queue for traversing
	
	to_be_visited.push(vertex);     // adding the start vertex into the queue
	visited[vertex] = true;         // mark it as visited
	std::cout << vertex << ' ';
	
	while (!to_be_visited.empty()) { // until we got vertices into the queue
		int current = to_be_visited.front(); // get the first one
		for (int i = 1; i < max; i++) {      // add all his unvisited neighbors 
 			if (adj_matrix[current][i] != 0 && !visited[i]) {
				to_be_visited.push(i);
				visited[i] = true;
				std::cout << i << ' ';
			}
		}
		to_be_visited.pop(); // remove the current vertex from the queue
	}
}

/**
* we mark that the given @vertex is now visited and print it on the standard output
* repeat the algorithm with the first unvisited @successor we hit of the given @vertex
*/
void dfs_helper(int vertex, bool visited[]) {

	visited[vertex] = true;
	std::cout << vertex << ' ';
	for (size_t i = 0; i < max; i++) {
		if (adj_matrix[vertex][i] && !visited[i]) {
			dfs_helper(i, visited);
		}
	}
}

void recursive_dfs(int vertex) {

	bool visited[max] = { false, }; // used to mark vertices as visited
	dfs_helper(vertex, visited);
}


/**
* each time current vertex is the top of stack (top) element
* if the current vertex is not already visited push to the stack all unvisited successor
* the algorithm repeats until there are no elements left in the stack
*/
void iterative_dfs(int vertex) {

	bool visited[max] = { false, };
	std::stack<int> to_be_visited; // a stack for traversing
	
	to_be_visited.push(vertex); // adding the start vertex into the stack
	
	while (!to_be_visited.empty()) {
		int current = to_be_visited.top();
		to_be_visited.pop();
		if (!visited[current]) {
			std::cout << current << ' ';
			for (int i = 1; i < max; i++) {
				if (adj_matrix[current][i] != 0 && !visited[i]) {
					to_be_visited.push(i);
				}
			}
			visited[current] = true;
		}
	}
}

int main() {

	init_graph();
	
	print_graph();

	std::cout << "the order of visited vertices by bfs is: ";
	bfs(1);
	std::cout << std::endl;

	std::cout << "the order of visited vertices by recursive dfs is: ";
	recursive_dfs(1);
	std::cout << std::endl;

	std::cout << "the order of visited vertices by iterative dfs is: ";
	iterative_dfs(1);
	std::cout << std::endl;

	return 0;
}
