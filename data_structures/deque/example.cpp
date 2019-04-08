/*******************************************************************************
 * This file is part of the "Data structures and algorithms" course. FMI 2018/19 
 *******************************************************************************/

/**
 * @file   example.cpp
 * @author Plamen Minev
 * @date   04.2019
 * @brief  Example usage and some tests
 *         for our implementation of 
 *         the deque.
 */

#include <iostream>   // std::cout
#include "deque.hpp"  // dsa::deque

int main() {
	
	dsa::deque<int> mydeque;
	std::cout << "print 1!\n\n";
	mydeque.print(std::cout);
	for (size_t i = 0; i < 50; i++) {
		mydeque.push_back(i);
	}
	std::cout << "print 2!\n\n";
	mydeque.print(std::cout);
	for (size_t i = 0; i < 16; i++) {
		mydeque.pop_back();
	}

	std::cout << "print 3!\n\n";
	mydeque.print(std::cout);
	for (size_t i = 0; i < 50; i++) {
		mydeque.push_front(i);
	}

	std::cout << "print 4!\n\n";
	mydeque.print(std::cout);
	for (size_t i = 0; i < 16; i++) {
		mydeque.pop_front();
	}
	std::cout << "print 5!\n\n";
	mydeque.print(std::cout);

	std::cout << "Front element " << mydeque.front()<<'\n';
	std::cout << "Last element " << mydeque.back()<< '\n';
	mydeque.pop_back();
	std::cout << "Last element after pop_back " << mydeque.back() << '\n';
	std::cout << "Last element using operator[]" << mydeque[mydeque.size()-1]<<'\n';

	dsa::deque<int> secondDeque(mydeque);
	std::cout << "\nCopied deque!\n";
	secondDeque.print(std::cout);

	for (size_t i = 0; i < 5; i++) {
		secondDeque.pop_back();
	}

	for (size_t i = 0; i < 5; i++) {
		secondDeque.pop_front();
	}

	std::cout << "Manipulated second deque!\n";
	secondDeque.print(std::cout);
	std::cout << "Debug print of first deque before operator=!\n";
	mydeque.print(std::cout);

	mydeque = secondDeque;

	std::cout << "Debug print of first deque after operator=!\n";
	mydeque.print(std::cout);
	return 0;
}
