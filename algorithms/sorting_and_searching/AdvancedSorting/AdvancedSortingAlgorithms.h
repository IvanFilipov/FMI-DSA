#pragma once

#include <algorithm> //std::swap

///Merge Sort
/// good sides : STABLE , difficulty in best , worst and average case : ~ O(nlogn)
/// bad sides : requires additional memory ~ O(n) ,not adaptive ( when elements are nearly sorted,
/// the difficulty is still O(nlogn) )

void merge(int *arr, int left, int right) {

	//additional memory for merging
	int* copy = new int[left + right];

	/// indexes of the first half , second and copied
	int leftIndex = 0, rightIndex = left, copyIndex = 0;


	//iterating both left and right parts
	//in each step we
	//take the smaller element form each part
	//and copy it in 'copy' array
	//in order to have sorted sequence in copy array at the end
	while (leftIndex < left && rightIndex < left + right)
		copy[copyIndex++] = (arr[leftIndex] < arr[rightIndex]) 
							? arr[leftIndex++] 
							: arr[rightIndex++];

	//we have elements left in the first half
	//just copy them in the sorted array 'copy'
	while (leftIndex < left)
		copy[copyIndex++] = arr[leftIndex++];

	while (rightIndex < left + right)
		copy[copyIndex++] = arr[rightIndex++];

	//copy the memory back into the given array
	memcpy(arr, copy, sizeof(int)*(left + right));

	//release the memory used
	delete[] copy;

};


void mergeSort(int* arr, int size) {

	if (size == 1)
		return;

	if (size == 2) {

		if (arr[0] > arr[1]) {
			std::swap(arr[0], arr[1]);
		}
		return;
	}

	int mid = size / 2;

	//dividing in two parts
	mergeSort(arr, mid);
	mergeSort(arr + mid, size - mid);

	//merging the two sorted parts into one array
	merge(arr, mid, size - mid);

}

///Quick Sort
/// good sides : maybe the fastest one in average case : O(nlogn) , 
/// additional memory for recursion calls
/// bad sides: worst case : O(n^2) , NOT STABLE

void quickSort(int* arr, int size) {

	//basic cases
	if (size == 1)
		return;

	if (size == 2) {

		if (arr[0] > arr[1]) {
			std::swap(arr[0], arr[1]);
		}
		return;
	}


	//partition phase
	int left = 0, right = size - 1;

	//not the smartest way to choose the pivot element
	//but the easiest to implement and to debug with
	//int pivot = arr[size / 2];
	
	//better median - of - three
	int pivot = std::max(std::min(arr[size/2], arr[size-1]),
									std::min(std::max(arr[size/2], arr[size-1]),
													  arr[0]));
	while (left <= right) {

		//finding the first available 
		//element in the left half
		while (arr[left] < pivot)
			left++;

		//in the right half
		while (arr[right] > pivot)
			right--;

		//swap them
		if (left <= right) {
			std::swap(arr[left], arr[right]);
			left++;
			right--;
		}

	}

	//sorting left half
	if (left < size)
		quickSort(arr + left, size - left);

	//sorting right half
	if (right > 0)
		quickSort(arr, right + 1);

}


///Heapsort 
///good sides : O(nlogn) difficulty in every case,
///no additional memory needed
///bad sides : not stable

//sifts down an element on position 'pos' into 
//a valid heap (arr)
void sift(int* arr, int pos, int size) {

	//which is the element we should sift
	int movedElem = arr[pos];
	int movedIndex = pos;

	//where the first child is
	int childIndex = pos + pos;

	//going down the heap
	//until the moved element
	//finds its own position
	while (childIndex < size) {

		//which child is the bigger one
		if (childIndex < size - 1 && arr[childIndex] < arr[childIndex + 1])
			childIndex++;

		//we should stop sift the elem down
		if (movedElem > arr[childIndex])
			break;

		//swapping the elem with it's greater child 
		arr[movedIndex] = arr[childIndex];

		//next step
		movedIndex = childIndex;
		childIndex *= 2;
	}

	//the elem have finally on it's position
	arr[movedIndex] = movedElem;
}


void heapSort(int* arr, int size) {

	//building the heap
	//notice that all elems after arr[size/2] are
	//actually leaves in the heap
	for (int i = size / 2 + 1; i > 1; i--)
		sift(arr, i - 1, size);

	//swapping the first elem with the last
	//then restore the heap
	for (int i = size - 1; i > 1; i--) {
		std::swap(arr[1], arr[i]);

		//restore heap phase
		sift(arr, 1, i);
	}

}

