/*******************************************************************************
 * This file is part of the "Data structures and algorithms" course. FMI 2018/19 
 *******************************************************************************/

/**
 * @file   example.cpp
 * @author Ivan Filipov
 * @date   10.2018
 * @brief  Example usage of our custom dynamic_stack.
 */
 
#include <iostream> // std::cout, std::endl

#include "dynamic_stack.hpp" // dsa::dynamic_stack

using dsa::dynamic_stack;

const int MAXN = 8; //!< number of additions/removals

int main() {

	dynamic_stack<int> s;

	for (int i = 0; i < MAXN; i++) {

		s.push(i + 1);
		std::cout << "elem " << s.top()
			      << " successfully added!\n";
	}
	std::cout << "current size : " << s.size() << std::endl << std::endl;

	for (int i = 0; i < MAXN; i++) {

		std::cout << "elem " << s.top();
		s.pop();
		std::cout << " successfully removed!\n";
	}
	std::cout << "current size : " << s.size() << std::endl << std::endl;


	for (int i = 0; i < MAXN - 3; i++) {

		s.push(i + 1);
		std::cout << "elem " << s.top()
				  << " successfully added!\n";
	}
	std::cout << "current size : " << s.size() << std::endl << std::endl;

	for (int i = 0; i < MAXN - 5; i++) {

		std::cout << "elem " << s.top();
		s.pop();
		std::cout << " successfully removed!\n";

	}
	std::cout << "current size : " << s.size() << std::endl << std::endl;

	std::cout << "top elem changed from " << s.top();
	s.top() = 10;
	std::cout << " to " << s.top() << std::endl;

	for (int i = 0; i < MAXN - 3; i++) {

		s.push(i + 1);
		std::cout << "elem " << s.top()
				  << " successfully added!\n";
	}
	
	std::cout << "\na copy s1?\n";
	dynamic_stack<int> s1 = s;
	while (!s1.empty()) {

		std::cout << "s1\'s top (" << s1.top()
				  << ") == s\'s top (" << s.top() 
				  << ")\n";
		s1.pop();
		s.pop();
	}

	return 0;
}
