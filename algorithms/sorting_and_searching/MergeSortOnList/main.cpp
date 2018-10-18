#include<stdlib.h> //rand(), srand()
#include<time.h> //time()

#include"LinkedList.hpp" //custom slightly linked list


int main(){

	LinkedList<int> list;

	srand(time(NULL));

	for (int i = 0; i < 10; i++)
		list.pushBack(rand() % 100);

	std::cout << "starting list items : \n";
	list.print();


	list.sort();
	std::cout << "sorted list items : \n";
	list.print();

	return 0;
}