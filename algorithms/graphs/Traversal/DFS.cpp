#include<stdio.h> //printf, putchar

//STL stuff
#include<array>
#include<vector>
#include<unordered_map>

const unsigned int MAX_VER_VAL = 26;

typedef char vertex;

using graph = std::unordered_map<vertex, std::vector<vertex>>;
using visitor = std::array<bool, MAX_VER_VAL + 1>;


graph G;

void initGraph() {

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

bool DFS(vertex current, vertex target, visitor& isVisited) {

	printf("-> %c", current);

	if (current == target)
		return true;
	

	isVisited[current - 'A'] = true;

	auto it = G.find(current);

	if (it == G.end()) {

		putchar('\n');

		return false;
	}

	for each (vertex adj in it->second) {

		if (!isVisited[adj - 'A']) {

			if (DFS(adj, target, isVisited))
				return true;

			printf("<- %c\n",adj);
		}

	}

	//putchar('\n');
	return false;

}


int main() {

	initGraph();

	vertex start = 'A';
	vertex target = 'P';

	printf("searching for vertex %c\n", target);

	visitor isVisited = { false };

	if (DFS(start, target, isVisited))
		printf("\nfound %c\n", target);
	else
		printf("\ncan't find %c\n",target);

	
	target = 'I';

	printf("\n\nsearching for vertex %c\n", target);

	isVisited.fill(false);

	if (DFS(start, target, isVisited))
		printf("\nfound elem %c\n", target);
	else
		printf("\ncan't find %c\n", target);

	return 0;
}
