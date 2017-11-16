#include "DynamicQueue.hpp"

const int MAXN = 8;

int main() {

	Queue<int> q;

	/* will make an exception
	for (int i = 0; i < MAXN + 1; i++)
	q.Enqueue(i);
	*/

	for (int i = 0; i < MAXN; i++) {

		q.enqueue(i + 1);
		std::cout << "elem " << q.back()
			<< " successfully added!\n";

	}

	std::cout << "\ncurrent size : " << q.getSize()
		<< std::endl;

	for (int i = 0; i < MAXN; i++) {

		std::cout << "elem " << q.front();
		q.dequeue();
		std::cout<< " successfully removed!\n";

	}

	std::cout << "\ncurrent size : " << q.getSize()
		<< std::endl;


	for (int i = 0; i < MAXN - 3; i++) {

		q.enqueue(i + 1);
		std::cout << "elem " << q.back()
			<< " successfully added!\n";

	}

	std::cout << "\ncurrent size : " << q.getSize()
		<< std::endl;

	for (int i = 0; i < MAXN - 5; i++) {

		std::cout << "elem " << q.front();
		q.dequeue();
		std::cout << " successfully removed!\n";

	}

	for (int i = 0; i < MAXN; i++) {

		q.enqueue(i + 1);
		std::cout << "elem " << q.back()
			<< " successfully added!\n";

	}

	Queue<int> q1 = q;

	while (!q1.isEmpty()) {

		std::cout << "q1\'s front (" << q.front()
			<< ") == q\'s front (" << q.front() << ")\n";

		q1.dequeue();
		q.dequeue();

	}


	std::cout << "\ncurrent size : " << q.getSize()
			  << std::endl;

	return 0;

}