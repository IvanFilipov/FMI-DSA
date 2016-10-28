#include"LinkedList.h"


int main(){

	LinkedList<int> list;


	list.PushBack(3);
	list.PushBack(11);
	list.PushBack(22); 
	list.PushBack(33);
	list.PushFront(44);
	list.PushFront(55);

	list.Print();

	if (list.Search(11)){

		std::cout << "yess";
	}

	for (LinkedList<int>::Iterator it = list.Beg(); it != list.End(); ++it) {

		std::cout<<*it;

	}


	return 0;

}