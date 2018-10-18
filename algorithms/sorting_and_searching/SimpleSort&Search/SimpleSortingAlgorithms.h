#pragma once
#include <algorithm> //std::swap

///Bubble sort 
///good sides : easy to implement , STABLE , fast when 
/// data is nearly sorted ~ O(n) , no additional memory is needed
///bad sides : difficulty ~ O(n^2) in worst , average case

void bubbleSort(int * arr, int size) {

	bool changeMade = true;

	for (int i = 0; i < size - 1 && changeMade; i++) {

		changeMade = false;

		for (int j = size - 1; j > i; j--) {

			if (arr[j - 1] > arr[j]) {
				std::swap(arr[j - 1], arr[j]);
				changeMade = true;
			}
		}
	}
}


///Selection sort
/// good sides : the easiest to implement , no additional memory is needed , less swaps than bubble and insertion sorts
/// bad sides : NOT STABLE , difficulty O(n^2) in best , worst and average case

void selectionSort(int *arr, int size) {

	int index;

	for (int i = 0; i < size - 1; i++) {

		index = i;

		for (int j = i + 1; j < size; j++)
			if (arr[index] > arr[j])
				index = j;

		std::swap(arr[i], arr[index]);
	}

}

///InsertionSort
///good sides : easy to implement , STABLE , fast when 
/// data is nearly sorted ~ O(n) , no additional memory is needed
///bad sides : difficulty ~ O(n^2) in worst , average case
void insertionSort(int *arr, int size) {

	for (int i = 1; i < size; i++)
		for (int j = i ; j > 0 && arr[j] < arr[j-1]; j--)
			std::swap(arr[j], arr[j-1]);

}

