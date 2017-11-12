#pragma once


//O(n) works always
int LinearSearch(int * arr, int size,int elem){

	for (int i = 0; i < size; i++)
		if (arr[i] == elem)
			return i;

	return -1;

}

//the array must be sorted - O(logN)
//array - left bound - right bound - searched element
int BinarySearch(int *arr,int L,int R,int elem) {

	//there is no such element
	if (L > R)
		return -1;

	size_t med = (L + R) / 2;

	if (arr[med] == elem)
		return med;

	if (arr[med] > elem)
		return BinarySearch(arr, L, med - 1, elem);

	if (arr[med] < elem)
		return BinarySearch(arr, med + 1, R,elem);

}


//K - step searching only for sorted array
//the time complexity of Jump Search is between LinearSearch and BinarySearch
//best result when step = sqrt(size)
int JumpSearch(int * arr, int size, int step, int elem) {

	if (step >= size)
		return LinearSearch(arr, size, elem);

	int ind;
	for (ind = 0; ind < size && arr[ind] < elem; ind += step)
		;

	int startInd = (ind + 1 < step) ? 0 : ind - step + 1;
	int endInd = (size < ind) ? size : ind;

	for (int i = startInd; i < endInd; i++)
		if (arr[i] == elem)
			return i;

	return -1;
}



