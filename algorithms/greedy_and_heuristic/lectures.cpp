/*******************************************************************************
 * This file is part of the "Data structures and algorithms" course. FMI 2018/19 
 *******************************************************************************/

/**
 * @file   lectures.cpp.cpp
 * @author Ivan Filipov
 * @date   02.2019
 * @brief  Taking maximum lectures without collisions
 *         task solution
 *         as an example of a greedy algorithm.
 */

#include <cstdio>    // std::printf()
#include <string>    // std::string
#include <vector>    // std::vector
#include <algorithm> // std::sort()

/// begin - end time for each lecture
using time_interval = std::pair<size_t, size_t>;
/// name - time interval for each lecture
using lecture = std::pair<std::string, time_interval>;
/// all lectures in a scheduler
using scheduler = std::vector<lecture>;
/// all lectures to be taken
scheduler sch;

/// initialize the scheduler with some lectures
void init() {

	sch = { 
		std::make_pair("Object Oriented Programming",    std::make_pair(3, 8)),
		std::make_pair("Introduction to Programming",    std::make_pair(7, 10)),
		std::make_pair("Data Structures and Algorithms", std::make_pair(5, 12)),
		std::make_pair("Data bases",                     std::make_pair(9, 14)),
		std::make_pair("Computer Graphics",              std::make_pair(13, 15)),
		std::make_pair("Internet of things",             std::make_pair(15, 19)),
		std::make_pair("Network security",               std::make_pair(17, 20))
	};
}

/// solve the task, by simply sorting all lectures by their end
/// time and take them one by one
void solve() {
	// sort by end time
	std::sort(sch.begin(), sch.end(), [](const lecture& a,const lecture& b) {
		return a.second.second < b.second.second;
	});
	// first lecture is selected
	printf("%s form %u to %u\n", sch[0].first.c_str(), 
		sch[0].second.first, sch[0].second.second);

	size_t last = 0, cur = 0;
	// take other lectures as so the
	// begin of current is after the end of last
	while (cur < sch.size() - 1) {
		cur++;
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
