#include "Queue.hpp"

const int MAXN = 8;

int main() {

	Queue<int> q(MAXN);

	/* will make an exception
	for (int i = 0; i < MAXN + 1; i++)
		q.Enqueue(i);
	*/

	for (int i = 0; i < MAXN; i++) {

		q.enqueue(i + 1);
		std::cout << "elem " << i + 1
			<< " successfully added!\n";

	}

	std::cout << "\ncurrent size : " << q.getNumElems()
		<< std::endl;

	for (int i = 0; i < MAXN; i++) {

		std::cout << "elem " << q.dequeue()
			<< " successfully removed!\n";

	}

	std::cout << "\ncurrent size : " << q.getNumElems()
		<< std::endl;


	for (int i = 0; i < MAXN - 3; i++) {

		q.enqueue(i + 1);
		std::cout << "elem " << i + 1
			<< " successfully added!\n";

	}

	std::cout << "\ncurrent size : " << q.getNumElems()
		<< std::endl;

	for (int i = 0; i < MAXN - 5; i++) {

		std::cout << "elem " << q.dequeue()
			<< " successfully removed!\n";

	}


	std::cout << "\ncurrent size : " << q.getNumElems()
		<< std::endl;

	return 0;

}