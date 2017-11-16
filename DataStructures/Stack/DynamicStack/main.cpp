#include "DynamicStack.hpp"

const int MAXN = 8;

int main() {

	DynamicStack<int> s;


	for (int i = 0; i < MAXN; i++) {

		s.push(i + 1);
		std::cout << "elem " << s.peek()
			<< " successfully added!\n";

	}

	std::cout << "\ncurrent size : " << s.getSize()
		<< std::endl;

	for (int i = 0; i < MAXN; i++) {

		std::cout << "elem " << s.peek();
		s.pop();
		std::cout<< " successfully removed!\n";

	}

	std::cout << "\ncurrent size : " << s.getSize()
		<< std::endl;


	for (int i = 0; i < MAXN - 3; i++) {

		s.push(i + 1);
		std::cout << "elem " << s.peek()
			<< " successfully added!\n";

	}

	std::cout << "\ncurrent size : " << s.getSize()
		<< std::endl;

	for (int i = 0; i < MAXN - 5; i++) {

		std::cout << "elem " << s.peek();
		s.pop();
		std::cout << " successfully removed!\n";

	}


	std::cout << "\ncurrent size : " << s.getSize()
		<< std::endl;
		
	std::cout << "top elem changed from " << s.peek();

	s.peek() = 10;

	std::cout << " to " << s.peek();



	for (int i = 0; i < MAXN - 3; i++) {

		s.push(i + 1);
		std::cout << "elem " << s.peek()
			<< " successfully added!\n";

	}

	DynamicStack<int> s1 = s;

	while (!s1.isEmpty()) {

		std::cout << "s1\'s top (" << s1.peek()
			<< ") == s\'s top (" << s.peek() << ")\n";

		s1.pop();
		s.pop();

	}


	return 0;

}