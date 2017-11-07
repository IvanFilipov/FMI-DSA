#include "DynamicQueue.hpp"

const int MAXN = 8;

int main() {

	Queue<int> q;

	/* will make an exception
	for (int i = 0; i < MAXN + 1; i++)
	q.Enqueue(i);
	*/

	for (int i = 0; i < MAXN; i++) {

		q.Enqueue(i + 1);
		std::cout << "elem " << q.Back()
			<< " successfully added!\n";

	}

	std::cout << "\ncurrent size : " << q.GetSize()
		<< std::endl;

	for (int i = 0; i < MAXN; i++) {

		std::cout << "elem " << q.Front();
		q.Dequeue();
		std::cout<< " successfully removed!\n";

	}

	std::cout << "\ncurrent size : " << q.GetSize()
		<< std::endl;


	for (int i = 0; i < MAXN - 3; i++) {

		q.Enqueue(i + 1);
		std::cout << "elem " << q.Back()
			<< " successfully added!\n";

	}

	std::cout << "\ncurrent size : " << q.GetSize()
		<< std::endl;

	for (int i = 0; i < MAXN - 5; i++) {

		std::cout << "elem " << q.Front();
		q.Dequeue();
		std::cout << " successfully removed!\n";

	}

	for (int i = 0; i < MAXN; i++) {

		q.Enqueue(i + 1);
		std::cout << "elem " << q.Back()
			<< " successfully added!\n";

	}

	Queue<int> q1 = q;

	while (!q1.isEmpty()) {

		std::cout << "q1\'s front (" << q.Front()
			<< ") == q\'s front (" << q.Front() << ")\n";

		q1.Dequeue();
		q.Dequeue();

	}


	std::cout << "\ncurrent size : " << q.GetSize()
		<< std::endl;

	return 0;

}