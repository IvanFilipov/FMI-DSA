#include "data_structures/deque/deque.hpp"
#include <iostream>

int main()
{
	dsa::deque<int> mydeque;
	std::cout << "print 1!\n\n";
	mydeque.print();
	for (int i = 0; i < 50; i++)
	{
		mydeque.push_back(i);
	}
	std::cout << "print 2!\n\n";
	mydeque.print();
	for (int i = 0; i < 16; i++)
	{
		mydeque.pop_back();
	}

	std::cout << "print 3!\n\n";
	mydeque.print();
	for (int i = 0; i < 50; i++)
	{
		mydeque.push_front(i);
	}

	std::cout << "print 4!\n\n";
	mydeque.print();
	for (int i = 0; i < 16; i++)
	{
		mydeque.pop_front();
	}
	std::cout << "print 5!\n\n";
	mydeque.print();

	std::cout << mydeque.front()<<'\n';
	std::cout << mydeque.back()<< '\n';
	mydeque.pop_back();
	std::cout << mydeque.back() << '\n';
	std::cout << mydeque[mydeque.size()-1]<<'\n';

	return 0;
}