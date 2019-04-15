
/*******************************************************************************
 * This file is part of the "Data structures and algorithms" course. FMI 2018/19 
 *******************************************************************************/

/**
 * @file   example.cpp
 * @author Ivan Filipov
 * @date   10.2018
 * @brief  Example usage of our custom static queue data structure.
 */
 
#include <iostream>

#include "static_queue.hpp"

using dsa::static_queue;
/// max number of elements
const size_t MAXN = 8;
/// how many elements to add/remove
const int ECOUNT = 8;

int main() {

	static_queue<int, MAXN> q;

	/* will throw an exception
	for (int i = 0; i < MAXN + 1; i++)
		q.enqueue(i);
	*/

	for (int i = 0; i < ECOUNT; i++) {
		q.push(i + 1);
		std::cout << "elem " << i + 1
			      << " successfully added!\n";
	}

	std::cout << "\ncurrent size : " 
	          << q.size() << std::endl;

	for (int i = 0; i < ECOUNT; i++) {
		std::cout << "elem " << q.pop()
			      << " successfully removed!\n";
	}

	std::cout << "\ncurrent size : " 
	          << q.size() << std::endl;


	for (int i = 0; i < ECOUNT - 3; i++) {
		q.push(i + 1);
		std::cout << "elem " << i + 1
			      << " successfully added!\n";
	}

	std::cout << "\ncurrent size : " 
	          << q.size() << std::endl;

	for (int i = 0; i < ECOUNT - 5; i++) {
		std::cout << "elem " << q.pop()
			      << " successfully removed!\n";
	}
	
	std::cout << "\ncurrent size : " 
	          << q.size() << std::endl;

	return 0;
}
