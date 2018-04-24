#include<ctime>
#include<iostream>
#include"PriorityQueue.h"

void Test_PriorityQueue()
{
	// Create queue
	auto cmp = [](const int& lhs, const int &rhs)->int
	{
		if (lhs > rhs) return 1;
		if (lhs < rhs) return -1;
		return 0;
	};

	PriorityQueue<int, decltype(cmp)> test(cmp);
	std::cout << "Successful created priority queue!\n\n";

	// Test whether container is empty
	std::cout << "Is empty: " << ((test.empty()) ? "True\n\n" : "False\n\n");

	// Get size
	std::cout << "Size: " << test.size() << "\n\n";

	// Get top element
	try
	{
		std::cout << "Get top element: ";
		std::cout << test.top() << std::endl;
	}
	catch (const std::exception& e )
	{
		std::cout << e.what()<<std::endl;
	}
	std::cout << std::endl;
	 // Insert elements
	srand(time(NULL));
	for (size_t i = 0; i < 10; i++)
	{
		unsigned el = rand() % 10;
		test.push(el);
		std::cout << "Successful added element: " << el << std::endl;
	}
	std::cout << std::endl;

	// Remove elements
	while (!test.empty())
	{
		std::cout << "See and pop the top element... " << test.top() << std::endl;
		test.pop();
	}
	std::cout << std::endl;

	// Insert new element
	test.push(100);
	std::cout << "Successful added element: " << 100 << "\n\n";

	// Clear queue
	std::cout << "Size before clear: " << test.size() << std::endl;
	test.clear();
	std::cout << "Size after clear: " << test.size() << std::endl;
}
int main()
{
	Test_PriorityQueue();

	system("pause");

	return 0;
}