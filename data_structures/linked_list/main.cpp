#include"LinkedList.hpp"


int main(){

	LinkedList<int> list;

	list.pushBack(3);
	list.pushBack(11);
	list.pushBack(22); 
	list.pushBack(33);

	list.pushFront(44);
	list.pushFront(55);

	list.print();

	if (list.search(11)){

		std::cout << "found!\n";
	}

	list.popBack();
	list.popFront();
	list.popBack();

	for (LinkedList<int>::Iterator it = list.begin(); it != list.end(); ++it) {

		std::cout<< *it << ' ' ;

	}

	LinkedList<int> second = list;

	std::cout << "copy ?\n";
	second.print();

	list.pushBack(25);
	list.pushBack(14);
	list.pushBack(18);
	list.pushBack(1);

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
			list.insertAfter(it,666);

	}

	for (auto& i : list) {
		std::cout << i << " ";
	}
	std::cout << '\n';

	//filter
	for (auto it = list.begin(); it != list.end(); ) {
		if (*it % 2 == 0) {
			it = list.eraseAfter(it);
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
			list.insertAfter(it, 666);

	}

	for (auto& i : list) {
		std::cout << i << " ";
	}
	std::cout << '\n';

	return 0;

}