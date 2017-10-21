#include "DynamicArray.hpp"
#include"stdlib.h"
#include"time.h"
#include"chrono"


//a func that fills our array with 10000 random elements
void Init(DynamicArray<int>& arr) {

	srand(time(0));
	
	for (int i = 0; i < 10000; i++)
		arr.PushBack(rand() % 1000);


}



int main(){

	
	DynamicArray<int> arr;

	Init(arr);

	/* TEST 1 linear  searching*/

	//using some dark c++ 11 magic to calculate the time 
	//needed from the function in microseconds
	// 1 second = 1000* 1 millisecond = 1000 * 1000 * 1 microsecond 


	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

	std::cout << "elem 200 on index :"
		<< arr.Search(200);

	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
	std::cout << "  for exactly "
		<< std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()
		<< " microseconds \n";


	std::cout << "Wait while sorting ...\n";
	arr.Sort();

	/* TEST 2 binary searching*/

	begin = std::chrono::steady_clock::now();

	std::cout << "elem 200 on index :"
		<< arr.Search(200);

	end = std::chrono::steady_clock::now();
	std::cout << "  for exactly "
		<< std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()
		<< " microseconds \n";

	//push / pop / addAt / removeAt tests

	DynamicArray<int> arr1;

	arr1.PushBack(7);
	arr1.PushBack(8);
	arr1.PushBack(9);
	arr1.PushBack(10);
	arr1.PushBack(15);
	arr1.PushBack(23);
	
	arr1.InsertAt(33, 25);
	arr1.InsertAt(4, 14);

	arr1.PrintElems();

	arr1.RemoveAt(58);
	arr1.RemoveAt(4);

	arr1.PrintElems();


	return 0;
}