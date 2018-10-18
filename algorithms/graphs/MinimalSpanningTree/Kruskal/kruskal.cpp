#include<stdio.h>

#include<list>
#include<tuple>
#include<array>

const int MAX_VER_VAL = 26;
const char NO_PARENT = '?';

typedef char vertex;
typedef unsigned int weight;

using edge = std::tuple<vertex, vertex, weight>;
using graph = std::list<edge>;
using parentList = std::array<vertex, MAX_VER_VAL + 1>;

graph G;

void initGraph() {

	G.push_front(std::make_tuple('A', 'B', 1));
	G.push_front(std::make_tuple('A', 'D', 2));
	G.push_front(std::make_tuple('B', 'C', 3));
	G.push_front(std::make_tuple('B', 'E', 13));
	G.push_front(std::make_tuple('C', 'D', 4));
	G.push_front(std::make_tuple('C', 'F', 3));
	G.push_front(std::make_tuple('D', 'F', 16));
	G.push_front(std::make_tuple('D', 'H', 14));
	G.push_front(std::make_tuple('E', 'F', 12));
	G.push_front(std::make_tuple('E', 'I', 13));
	G.push_front(std::make_tuple('E', 'J', 1));
	G.push_front(std::make_tuple('F', 'H', 1));
	G.push_front(std::make_tuple('H', 'I', 1));

}


bool cmp(const edge& e1, const edge& e2) {

	return (std::get<2>(e1) < std::get<2>(e2));

}


size_t findRoot(size_t index, const parentList& pl) {

	while (pl[index] != NO_PARENT)
		index = pl[index];

	return index;
}

void kruskal(parentList& pl) {

	//initialize all in different subsets
	pl.fill(NO_PARENT);

	unsigned int wMST = 0;

	//sorting all edges depending on their weights
	G.sort(cmp);

	size_t r1, r2;

	for (auto edge : G) {

		//the sub-set's root in which the first vertex is
		r1 = findRoot(std::get<0>(edge) - 'A', pl);
		r2 = findRoot(std::get<1>(edge) - 'A', pl);

		//if they are not in the same subset
		if (r1 != r2) {

			printf("(%c, %c) ", std::get<0>(edge), std::get<1>(edge));

			wMST += std::get<2>(edge);
			
			//join the two subsets
			pl[r2] = r1;
		}

	}

	printf("\n Tree weight : %u\n", wMST);
}


int main() {

	initGraph();

	parentList pl;

	kruskal(pl);

	return 0;

}