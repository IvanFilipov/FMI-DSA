#include "DynamicArray.hpp"
#include"stdlib.h"
#include"time.h"
#include"chrono"


//a func that fills our array with 10000 random elements
void init(DynamicArray<int>& arr) {

	srand(time(0));
	
	for (int i = 0; i < 10000; i++)
		arr.pushBack(rand() % 1000);


}


int main(){

	
	DynamicArray<int> arr;

	init(arr);

	/* TEST 1 linear  searching*/

	//using some dark c++ 11 magic to calculate the time 
	//needed from the function in microseconds
	// 1 second = 1000* 1 millisecond = 1000 * 1000 * 1 microsecond 


	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

	std::cout << "elem 200 on index :"
		<< arr.search(200);

	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
	std::cout << "  for exactly "
		<< std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()
		<< " microseconds \n";


	std::cout << "Wait while sorting ...\n";
	arr.sort();

	/* TEST 2 binary searching*/

	begin = std::chrono::steady_clock::now();

	std::cout << "elem 200 on index :"
		<< arr.search(200);

	end = std::chrono::steady_clock::now();
	std::cout << "  for exactly "
		<< std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()
		<< " microseconds \n";

	//push / pop / addAt / removeAt tests

	DynamicArray<int> arr1;

	arr1.pushBack(7);
	arr1.pushBack(8);
	arr1.pushBack(9);
	arr1.pushBack(10);
	arr1.pushBack(15);
	arr1.pushBack(23);
	
	arr1.insertAt(33, 25);
	arr1.insertAt(4, 14);

	arr1.printElems();

	arr1.removeAt(58);
	arr1.removeAt(4);

	arr1.printElems();


	return 0;
}