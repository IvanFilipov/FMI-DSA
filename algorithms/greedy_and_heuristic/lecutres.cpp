#include<stdio.h>
#include<string>
#include<vector>
#include <algorithm> //std::sort

//task : taking maximum lectures without collisions

//begin - end time for each lecture
using time = std::pair<size_t, size_t>;

//name - time for each lecture
using lecture = std::pair<std::string, time>;

using scheduler = std::vector<lecture>;

scheduler sch;

void init() {

	sch = { std::make_pair("Object Oriented Programming",std::make_pair(3, 8)),
		std::make_pair("Introduction to Programming", std::make_pair(7, 10)),
		std::make_pair("Data Structures and Algorithms", std::make_pair(5, 12)),
		std::make_pair("Data bases", std::make_pair(9, 14)),
		std::make_pair("Computer Graphics", std::make_pair(13, 15)),
		std::make_pair("Internet of things", std::make_pair(15, 19)),
		std::make_pair("Network security", std::make_pair(17, 20))
	};


}

void solve() {

	std::sort(sch.begin(), sch.end(), [](const lecture& a,const lecture& b){

		//sorting by end time
		return a.second.second < b.second.second;

	});

	//first lecture is selected
	printf("%s form %u to %u\n", sch[0].first.c_str(), 
		sch[0].second.first, sch[0].second.second);

	size_t last = 0, cur = 0;

	while (cur < sch.size() - 1) {

		cur++;

		//begin of current is after the end of last
		if (sch[cur].second.first > sch[last].second.second) {

			last = cur;

			printf("%s form %u to %u\n", sch[cur].first.c_str(),
				sch[cur].second.first, sch[cur].second.second);

		}
	}

}



int main() {

	init();
	solve();

	return 0;
}