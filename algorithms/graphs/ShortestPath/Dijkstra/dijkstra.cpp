#include<stdio.h> //printf, putchar
#include<limits.h> //UINT_MAX

//STL stuff
#include<array>
#include<vector>
#include<queue>
#include<unordered_map>

const unsigned int MAX_VER_VAL = 26;
const char NO_PARENT = '?';
const unsigned int MAX_DISTANCE = UINT_MAX;

typedef char vertex;
typedef unsigned int weight;

using vwpair = std::pair<vertex, weight>;
using graph = std::unordered_map<vertex, std::vector<vwpair>>;


using parentsList = std::array<vertex,MAX_VER_VAL + 1>;
using distanceVector = std::array<weight, MAX_VER_VAL + 1>;
using visitor = std::array<bool, MAX_VER_VAL + 1>;

graph G;

void initGraph() {

	G['A'] = { {'B', 5}, {'F', 8} };
	G['B'] = { {'C', 4}, {'D', 1} };
	G['C'] = { {'F', 9}, {'H', 23} };
	G['D'] = { {'L', 3} };
	G['F'] = { {'I', 5}, {'K', 6} };
	G['H'] = { {'I', 11} };
	G['I'] = { {'J', 3} };
	G['J'] = { {'K', 2} };
	G['K'] = { {'L', 15} };
	G['L'] = { {'H', 6}, {'A', 18} };

}

auto cmp = [](const vwpair& f, const vwpair& s) -> bool {

	return f.second > s.second;

};


void dijkstra(vertex s,parentsList& pl, distanceVector& dv) {

	pl.fill(NO_PARENT);
	dv.fill(MAX_DISTANCE);

	dv[s - 'A'] = 0;

	// the set of all vertexes
	visitor done = { false };

	//all the vertexes we can see at a moment,
	//sorted by the cost of the shortest known path to them
	std::priority_queue<
		vwpair, //vertex - current path cost
		std::vector<vwpair>, //allocator
		decltype(cmp)> //the compare function
		wave(cmp);


	wave.push(std::make_pair(s, dv[s - 'A']));

	while (!wave.empty()) {
		
		//taking the best 
		auto cur = wave.top();
		wave.pop();

		//we are done with this vertex
		done[cur.first - 'A'] = true;

		auto it = G.find(cur.first);

		//there is't a list for this vertex
		if (it == G.end())
			continue;

		for each (vwpair adj in it->second) {

			if (!done[adj.first - 'A']) {

				//trying to optimize
				//the current path cost
				if (dv[adj.first - 'A'] > //the best known before
					dv[cur.first - 'A'] + adj.second) { //the best to current 
													 //+ the edge between them

					//adding to the parent list
					pl[adj.first - 'A'] = cur.first;
					//optimize the distance
					dv[adj.first - 'A'] = dv[cur.first - 'A'] + adj.second;

					wave.push(std::make_pair(adj.first, dv[adj.first - 'A']));

				}
			}
		}
	}
}

void printPath(vertex s, vertex e, const parentsList& pl) {

	if (pl[e - 'A'] != s)
		printPath(s, pl[e - 'A'], pl);

	printf("->%c", e);

}


int main() {

	initGraph();

	parentsList pl;
	distanceVector dv;

	vertex start = 'A';

	dijkstra(start, pl, dv);

	for (size_t i = 0; i < dv.size() - 1; i++){

		printf("Path between %c and %c :", start, 'A' + i);//, start);

		if (dv[i] == MAX_DISTANCE)
			printf("no such path!\n");
		else {

			printf(" %c", start);

			if (pl[i] != NO_PARENT)
				printPath(start, i + 'A', pl);

			printf("\ndistance : %u \n\n", dv[i]);
		}

	}

	return 0;
}