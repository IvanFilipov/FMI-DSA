#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <utility>
#include <unordered_map>
#include <unordered_set>
#include <limits.h>
#include <stdlib.h>
#include <time.h> 

using Weight = float;
using Vertex = char; 
using Edge = std::pair<Weight, Vertex>; 
using Children = std::vector<Edge>;
using Graph = std::unordered_map<Vertex, Children>;
using MST = std::unordered_map<Vertex, Vertex>;

// Constructs edge to vertex with given weight.
Edge edge(const Weight& w, const Vertex& to) {
	return std::make_pair(w, to);
}

Weight takeWeightFromEdge(const Edge& e) {
	return e.first;
}

Vertex takeVertexFromEdge(const Edge& e) {
	return e.second;
}

bool isInMst(const Vertex& v, const std::unordered_set<Vertex>& m) {
	return m.find(v) != m.end(); 
}

// Gets current smallest weight to vertex.
// If the vertex is not visited, returns INT_MAX (c++ equivalent of +infinity).
Weight getWeight(const Vertex& v, const std::unordered_map<Vertex, Weight>& cost) {
	auto weight_it = cost.find(v);
	if (weight_it == cost.end()) 
		return INT_MAX;
	return weight_it->second;
}

// Returns Minimal spanning tree by Prim's algorithm for directed graphs.
// Uses begin as starting vertex .
MST prim(Graph& g, Vertex begin) {
	MST mst;
	std::unordered_set<Vertex> inMst;

	// The map stores the smallest weight to given vertex.
	std::unordered_map<Vertex, Weight> cost;
	
	// The queue uses the natural order of edges(pairs).
	// First pop the edges with less weight.
	std::priority_queue<Edge, Children, std::greater<Edge>> q;

	Edge start = edge(0, begin);
	q.push(start);

	while (!q.empty()) {
		Edge to_child = q.top(); q.pop();
		Vertex vertex = takeVertexFromEdge(to_child);
		inMst.insert(vertex);
		
		// Iterates over the children of vertex
		for (Edge e : g[vertex]) {
			Vertex child = takeVertexFromEdge(e);
			Weight weight = takeWeightFromEdge(e);
		
			// Get current best weight for child or +inf if not visited
			Weight weight_current = getWeight(child, cost);
			if (!isInMst(child, inMst) && weight_current > weight) {
				mst[child] = vertex;
				cost[child] = weight;
				q.push(e);
			}
		}
	}
	return mst;
}

// Returns random vertex from given graph
Vertex get_rand_vertex(const Graph& g) {
	srand (time(NULL));
	auto it_to_rand_el = std::next(g.begin(), rand() % g.size());
	return it_to_rand_el->first;
}

MST primRandomBegin(Graph& g) {
	Vertex begin = get_rand_vertex(g);
	return prim(g, begin);
}

void printMst(const MST& m) {
	for (const std::pair<const Vertex, const Vertex>& p : m) {
		Vertex v1 = p.second, v2 = p.first;
		std::cout << "(" << v1 <<  ", " << v2 << ")" << std::endl; 
	}
}

Graph initGraph() {
	Edge a2b = edge(15, 'b'),
		 a2c = edge(3, 'c'),
		 a2d = edge(5, 'd'),
		 b2e = edge(1, 'e'),
		 c2b = edge(2, 'b'),
		 c2d = edge(1, 'd'),
		 d2e = edge(7, 'e'),
		 e2a = edge(1, 'e'),
		 e2c = edge(6, 'e');
		
	Graph g;
	g['a'] = { a2b, a2c, a2d };
	g['b'] = { b2e };
	g['c'] = { c2b, c2d };
	g['d'] = { d2e };	
	g['e'] = { e2a, e2c };	
	return g; 
}

int main() {
	Graph g = initGraph();
	MST m = prim(g, 'a');
	printMst(m);

	return 0;
}
