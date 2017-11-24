#include<fstream>
#include<iostream>

#include "StudentQueue.h"

using std::string;
using std::cout;

int main() {

	std::ifstream input("students.txt");

	if (!input.is_open()) {

		std::cerr << "can't open the file!\n";
		return -1;
	}

	StudentQueue queue;
	Student curStudent;

	unsigned int timer = 0;

	//reading all the input
	//and pop front if the first student is ready
	do {

		input >> curStudent.name >> curStudent.groupId;

		curStudent.enqTime = timer;

		//last reading was successful, and end-of-file bit is still down
		if (input)
			queue.enqueue(curStudent);
	

		//time > 0 and time even
		if (timer && timer % 2 == 0) {

			//time in waiting for each student is current time - enqueue time
			std::cout << queue.front().name << ' '
				<< timer - queue.front().enqTime << ".m\n";

			queue.dequeue();
		}

		++timer;

	} while (!input.eof());

	input.close(); //release the file descriptor

	//odd time -> move one minute forward
	if (timer & 1)
		++timer;

	//we don't have any more input
	//we should only output on each two minutes 
	while (!queue.isEmpty()) {

		std::cout << queue.front().name << ' ' 
			<< timer - queue.front().enqTime << ".m\n";

		queue.dequeue();

		timer += 2;
	}

	return 0;

}
