#include"LinkedList.hpp"


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

		std::cout << "found!\n";
	}

	list.PopBack();
	list.PopFront();
	list.PopBack();

	for (LinkedList<int>::Iterator it = list.begin(); it != list.end(); ++it) {

		std::cout<< *it << ' ' ;

	}

	LinkedList<int> second = list;

	std::cout << "copy ?\n";
	second.Print();

	list.PushBack(25);
	list.PushBack(14);
	list.PushBack(18);
	list.PushBack(1);

	std::cout << "modern C++ tests \n\n";

	//modern C++ look-like iterations

	//because our class has iterator support plus 
	//begin and end methods
	for (auto& i : list) {
		std::cout << i << " ";
	}
	std::cout << '\n';

	//insert after specific element
	for (LinkedList<int>::Iterator it = list.begin(); it != list.end(); ++it) {

		if(*it == 25)
			list.InsertAfter(it,666);

	}

	for (auto& i : list) {
		std::cout << i << " ";
	}
	std::cout << '\n';

	//filter
	for (auto it = list.begin(); it != list.end(); ) {
		if (*it % 2 == 0) {
			it = list.EraseAfter(it);
		}
		else {
			++it;
		}
	}

	for (auto& i : list) {
		std::cout << i << " ";
	}
	std::cout << '\n';

	//map +1
	for (LinkedList<int>::Iterator it = list.begin(); it != list.end(); ++it) {

		(*it)++;
	}
	for (auto& i : list) {
		std::cout << i << " ";
	}
	std::cout << '\n';



	//insert back
	for (LinkedList<int>::Iterator it = list.begin(); it != list.end(); ++it) {

		if (*it == 19)
			list.InsertAfter(it, 666);

	}

	for (auto& i : list) {
		std::cout << i << " ";
	}
	std::cout << '\n';

	return 0;

}