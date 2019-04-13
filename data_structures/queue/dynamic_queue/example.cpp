/*******************************************************************************
 * This file is part of the "Data structures and algorithms" course. FMI 2018/19 
 *******************************************************************************/

/**
 * @file   example.cpp
 * @author Ivan Filipov
 * @date   10.2018
 * @brief  Tests and example usage of our custom dynamic_queue.
 */

#include <iostream> // std::cin, std::endl

#include "dynamic_queue.hpp" // dsa::dynamic_queue

using dsa::dynamic_queue;
/// number of elements to add/remove
const int MAXN = 8;

int main() {

	dynamic_queue<int> q;

	for (int i = 0; i < MAXN; i++) {
		q.push(i + 1);
		std::cout << "elem " << q.back()
			      << " successfully added!\n";
	}

	std::cout << "\ncurrent size : "
	          << q.size() << std::endl;

	for (int i = 0; i < MAXN; i++) {
		std::cout << "elem " << q.front();
		q.pop();
		std::cout << " successfully removed!\n";
	}

	std::cout << "\ncurrent size : "
	          << q.size() << std::endl;


	for (int i = 0; i < MAXN - 3; i++) {
		q.push(i + 1);
		std::cout << "elem " << q.back()
				  << " successfully added!\n";
	}

	std::cout << "\ncurrent size : "
	          << q.size() << std::endl;

	for (int i = 0; i < MAXN - 5; i++) {
		std::cout << "elem " << q.front();
		q.pop();
		std::cout << " successfully removed!\n";
	}

	for (int i = 0; i < MAXN; i++) {
		q.push(i + 1);
		std::cout << "elem " << q.back()
			      << " successfully added!\n";
	}

	dynamic_queue<int> q1 = q;

	while (!q1.empty()) {
		std::cout << "q1\'s front (" << q.front()
			      << ") == q\'s front (" << q.front() << ")\n";
		q1.pop();
		q.pop();
	}

	std::cout << "\ncurrent size : "
	          << q.size() << std::endl;

	return 0;
}
