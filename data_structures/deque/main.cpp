#include "deque.hpp"
#include <iostream>

int main()
{
	dsa::deque<int> mydeque;
	std::cout << "print 1!\n\n";
	mydeque.print();
	for (size_t i = 0; i < 50; i++) {
		mydeque.push_back(i);
	}
	std::cout << "print 2!\n\n";
	mydeque.print();
	for (size_t i = 0; i < 16; i++) {
		mydeque.pop_back();
	}

	std::cout << "print 3!\n\n";
	mydeque.print();
	for (size_t i = 0; i < 50; i++) {
		mydeque.push_front(i);
	}

	std::cout << "print 4!\n\n";
	mydeque.print();
	for (size_t i = 0; i < 16; i++) {
		mydeque.pop_front();
	}
	std::cout << "print 5!\n\n";
	mydeque.print();

	std::cout << "Front element " << mydeque.front()<<'\n';
	std::cout << "Last element " << mydeque.back()<< '\n';
	mydeque.pop_back();
	std::cout << "Last element after pop_back " << mydeque.back() << '\n';
	std::cout << "Last element using operator[]" << mydeque[mydeque.size()-1]<<'\n';

	dsa::deque<int> secondDeque(mydeque);
	std::cout << "\nCopied deque!\n";
	secondDeque.print();

	for (size_t i = 0; i < 5; i++) {
		secondDeque.pop_back();
	}

	for (size_t i = 0; i < 5; i++) {
		secondDeque.pop_front();
	}

	std::cout << "Manipulated second deque!\n";
	secondDeque.print();
	std::cout << "Debug print of first deque before operator=!\n";
	mydeque.print();

	mydeque = secondDeque;

	std::cout << "Debug print of first deque after operator=!\n";
	mydeque.print();
	return 0;
}