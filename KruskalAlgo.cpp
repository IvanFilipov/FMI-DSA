#include<iostream>
#include<list>

const int MAXN = 200;
const int NO_PARENT = INT_MIN;

int prev[MAXN + 1];

struct Edge {

	int Va;
	int Vb;
	int w;

	Edge(int x = 0, int y = 0, int _w = 0) {

		Va = x ;
		Vb = y;
		w = _w;

	}

};

bool Comp(const Edge& e1, const Edge& e2) {

	return (e1.w < e2.w);

}


int FindRoot(int index) {

	while (prev[index] != NO_PARENT)
		index = prev[index];

	return index;
}

void Kruskal(std::list<Edge>& Graph) {

	int wMST = 0;

	//sorting all edges depending on their weights
	Graph.sort(Comp);

	int r1, r2; // cur edge vertexes
	

	for (std::list<Edge>::iterator it = Graph.begin(); it != Graph.end(); ++it) {

		r1 = FindRoot(it->Va);
	    r2 = FindRoot(it->Vb);

		if (r1 != r2) {

			std::cout << "(" << r1 << " , " << r2 << " ) ; ";
			wMST += it->w;
			prev[r2] = r1;
		}

	}


	std::cout <<"\n Tree weight : " << wMST << '\n';

}


void GraphInit(std::list<Edge>& G) {

	G.push_front(Edge(1,2,1));
	G.push_front(Edge(1, 4, 2));
	G.push_front(Edge(2, 3, 3));
	G.push_front(Edge(2, 5, 13));
	G.push_front(Edge(3, 4, 4));
	G.push_front(Edge(3, 6, 3));
	G.push_front(Edge(4, 6, 16)); 
	G.push_front(Edge(4, 7, 14));
	G.push_front(Edge(5, 6, 12));
	G.push_front(Edge(5, 8, 1));
	G.push_front(Edge(5, 9, 13));
	G.push_front(Edge(6, 7, 1));
	G.push_front(Edge(6, 9, 1));
	


}

void PrevInit() {

	for (int i = 0; i < MAXN + 1; i++)
		prev[i] = NO_PARENT;

}



int main() {

	
	std::list<Edge> Graph;

	PrevInit();
	GraphInit(Graph);

	Kruskal(Graph);
	return 0;

}