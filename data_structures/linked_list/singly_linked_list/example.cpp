#include <iostream>
#include "slinked_list.hpp"

void run_basic_tests() {
	
	slinked_list<int> f_list;

	f_list.push_back(1);
	f_list.push_back(11);
	f_list.push_back(22); 
	f_list.push_back(33);
	std::cout << "list after push_back some elements" << std::endl;
	f_list.print_elems(std::cout);
	
	f_list.push_front(44);
	f_list.push_front(55);
	std::cout << "\nlist after push_front 44, then 55" << std::endl;
	f_list.print_elems(std::cout);
	
	std::cout << "\nsearching for 11 :" << std::endl;
	slinked_list<int>::iterator it = f_list.find(11);
	if (it != f_list.end()) {

		std::cout << "found 11!" << std::endl;
		std::cout << "inserting 73 after it :" << std::endl;
		f_list.insert_after(it, 73);
		f_list.print_elems(std::cout);
	} else std::cout << "11 not found!" << std::endl;
	
	std::cout << "\nsearching for 1 :" << std::endl;
	it = f_list.find(1);
	if (it != f_list.end()) {

		std::cout << "found 1!" << std::endl;
		std::cout << "removing element after it :" << std::endl;
		f_list.remove_after(it);
		f_list.print_elems(std::cout);
	} else std::cout << "1 not found!" << std::endl;
	
	std::cout << "\nsearching for 404 :" << std::endl;
	it = f_list.find(404);
	if (it != f_list.end()) {

		std::cout << "found 404!" << std::endl;
		std::cout << "inserting 405 after it :" << std::endl;
		f_list.insert_after(it, 405);
		f_list.print_elems(std::cout);
	} else std::cout << "404 not found!" << std::endl;
	
	std::cout << "\nafter pop back :" << std::endl;
	f_list.pop_back();
	f_list.print_elems(std::cout);
	
	std::cout << "\nafter pop front :" << std::endl;
	f_list.pop_front();
	f_list.print_elems(std::cout);
	
	std::cout << "\nafter pop back :" << std::endl;
	f_list.pop_back();
	f_list.print_elems(std::cout);
	
	std::cout << "\nfirst element : " << f_list.front();
	std::cout << "after changing it to 101 : " << std::endl;
	f_list.front()  = 101;
	f_list.print_elems(std::cout);
	
	std::cout << "\nlast element : " << f_list.back();
	std::cout << "after changing it to 202 : " << std::endl;
	f_list.back()  = 202;
	f_list.print_elems(std::cout);
	
	
	slinked_list<int> second = f_list;
	std::cout << "\ncopy working?\n";
	second.print_elems(std::cout);
	
}	

void run_advanced_tests() {
	
	std::cout << "\nmodern C++ tests : TODO \n\n";
	//modern C++ look-like iterations
	//custom iterator algorithms
	//STL algorithms?
	//TO DO : add and explain advanced usages
}

int main() {
	
	/* testing the interface of the class */
	run_basic_tests();
	
	/* testing the modern C++ usage of the class */
	run_advanced_tests();
		
	return 0;
}
