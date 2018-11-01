/*
 * Example usage of a custom static queue data structure.
 * This file is part of the "Data structures and algorithms" course. FMI 2018/19
 *
 * Author : Ivan Filipov	
 */

#include <iostream>
#include "dynamic_queue.hpp"

using dsa::dynamic_queue;

const int MAXN = 8;

int main() {

	dynamic_queue<int> q;

	for (int i = 0; i < MAXN; i++) {

		q.push(i + 1);
		std::cout << "elem " << q.back()
			<< " successfully added!\n";
	}

	std::cout << "\ncurrent size : " << q.size()
		<< std::endl;

	for (int i = 0; i < MAXN; i++) {

		std::cout << "elem " << q.front();
		q.pop();
		std::cout<< " successfully removed!\n";

	}

	std::cout << "\ncurrent size : " << q.size()
		<< std::endl;


	for (int i = 0; i < MAXN - 3; i++) {

		q.push(i + 1);
		std::cout << "elem " << q.back()
			<< " successfully added!\n";

	}

	std::cout << "\ncurrent size : " << q.size()
		<< std::endl;

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

	std::cout << "\ncurrent size : " << q.size()
			  << std::endl;

	return 0;
}
