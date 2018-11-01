/*
 * Example usage of a custom static queue data structure.
 * This file is part of the "Data structures and algorithms" course. FMI 2018/19
 *
 * Author : Ivan Filipov	
 */
 
#include <iostream>
#include "static_queue.hpp"

using dsa::static_queue;

const size_t MAXN = 8;
const int ECOUNT = 8;

int main() {

	static_queue<int, MAXN> q;

	/* will make an exception
	for (int i = 0; i < MAXN + 1; i++)
		q.enqueue(i);
	*/

	for (int i = 0; i < ECOUNT; i++) {

		q.push(i + 1);
		std::cout << "elem " << i + 1
			<< " successfully added!\n";

	}

	std::cout << "\ncurrent size : " << q.size()
		<< std::endl;

	for (int i = 0; i < ECOUNT; i++) {

		std::cout << "elem " << q.pop()
			<< " successfully removed!\n";

	}

	std::cout << "\ncurrent size : " << q.size()
		<< std::endl;


	for (int i = 0; i < ECOUNT - 3; i++) {

		q.push(i + 1);
		std::cout << "elem " << i + 1
			<< " successfully added!\n";

	}

	std::cout << "\ncurrent size : " << q.size()
		<< std::endl;

	for (int i = 0; i < ECOUNT - 5; i++) {

		std::cout << "elem " << q.pop()
			<< " successfully removed!\n";

	}

	std::cout << "\ncurrent size : " << q.size()
		<< std::endl;

	return 0;
}
