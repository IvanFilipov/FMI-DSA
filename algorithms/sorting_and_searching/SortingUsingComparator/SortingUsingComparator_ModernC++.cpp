#include<iostream>
#include<algorithm>
#include<array>
#include<functional>


typedef unsigned int _type_data;
struct Elem {

	int key;

	//no matter what data we got here
	_type_data data;
	
};

bool operator<(const Elem& lhs, const Elem& rhs) {

	return lhs.key < rhs.key;
}

bool operator>(const Elem& lhs, const Elem& rhs) {

	return lhs.key > rhs.key;
}

std::ostream& operator<<(std::ostream& os, const Elem& e) {

	return os << "{ key :" << e.key
		<< " , data : " << e.data
		<< " }";
}


int const SIZE = 6;
int main() {

	std::array<Elem, SIZE> arr = { { { 10,20 },{ 30,14 },{ -5,14 },{ 77,347 },{ 24,81 } ,{ 11, 15 } } };

	std::cout << "given elements :\n";
	for (auto it : arr) {
		std::cout << it << " ";
	}
	std::cout << "\n\n";

	std::sort(arr.begin(), arr.end());

	std::cout << "sorted by operator< :\n";
	for (auto it : arr) {
		std::cout << it << " ";
	}
	std::cout << "\n\n";
	
	std::sort(arr.begin(), arr.end(),std::greater<Elem>());

	std::cout << "sorted by std::greater<Elem> :\n";
	for (auto it : arr) {
		std::cout << it << " ";
	}
	std::cout << "\n\n";


	std::cout << "sorted by custom lambda function :\n";
	std::sort(arr.begin(), arr.end(), [](const Elem& lhs, const Elem& rhs) {
		return lhs.key < rhs.key;
	});
	for (auto it : arr) {
		std::cout << it << " ";
	}
	std::cout << "\n\n";

	
	return 0;
}