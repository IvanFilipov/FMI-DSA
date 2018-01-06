#include<stdio.h> //printf, putchar

//STL stuff
#include<queue>
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


void BFS(vertex start) {

	visitor isVisited = { false, };

	std::queue<vertex> wave;

	wave.push(start);

	while (!wave.empty()) {

		printf("from %c : ", wave.front());
		
		//will return iterator to the element if found
		//end iterator else
		auto it = G.find(wave.front());

		if (it == G.end()) {

			putchar('\n');
			wave.pop();
			continue;
		}


		for each (vertex adj in it->second) {

			if (!isVisited[adj - 'A']) {

				printf("%c ", adj);
				isVisited[adj - 'A'] = true;

				wave.push(adj);
			}

		}
		
		putchar('\n');
		wave.pop();

	}

	printf("traverse completed!\n");
}


int main() {

	initGraph();

	vertex start = 'A';

	BFS(start);

	return 0;

}
