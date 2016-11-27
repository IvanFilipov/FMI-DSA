#include<cstring> // memcpy



///simple swap function

void Swap(int& a, int& b) {

	int temp = a;
	a = b;
	b = temp;

}


///Counting sort
///good sides : O(n)
///bad sides : O((maxElem)) additional memory

//unsigned chars have values in [0 , 255]  

int const MAX_VAL = 255;
void CountingSort(unsigned char *arr, int size) {

	int helpArr[MAX_VAL + 1] = { 0 , };



	for (int i = 0; i < size; i++)
		helpArr[arr[i]]++;

	int j = 0;
	for (unsigned char i = 0; i < MAX_VAL; i++)
		while (helpArr[i]--)
			arr[j++] = i;


}



///Bubble sort 
///good sides : easy to implement , STABLE , fast when 
/// data is nearly sorted ~ O(n) , no additional memory is needed
///bad sides : difficulty ~ O(n^2) in worst , average case

void BubbleSort(int * arr, int size) {

	bool changeMade = true;

	for (int i = 0; i < size - 1 && changeMade; i++) {

		changeMade = false;

		for (int j = size - 1; j > i; j--) {

			if (arr[j - 1] > arr[j]) {
				Swap(arr[j - 1], arr[j]);
				changeMade = true;
			}
		}
	}
}


///Selection sort
/// good sides : the easiest to implement , no additional memory is needed , less swaps than bubble and insertion sorts
/// bad sides : NOT STABLE , difficulty O(n^2) in best , worst and average case

void SelectionSort(int *arr, int size) {

	for (int i = 0; i < size - 1; i++) {
		for (int j = i + 1; j < size; j++)
			if (arr[i] > arr[j])
				Swap(arr[i], arr[j]);
	}
}

///InsertionSort
///good sides : easy to implement , STABLE , fast when 
/// data is nearly sorted ~ O(n) , no additional memory is needed
///bad sides : difficulty ~ O(n^2) in worst , average case


void InsertionSort(int *arr, int size) {

	///helps us to find the min elem

	for (int i = size - 1; i > 0; i--)
		if (arr[i] < arr[i - 1])
			Swap(arr[i], arr[i - 1]);


	///real sorting
	for (int i = 2; i < size; i++)
		for (int j = i - 1; j > 0 && arr[j] > arr[i]; j--)
			Swap(arr[i], arr[j]);


}


///Merge Sort
/// good sides : STABLE , difficulty in best , worst and average case : ~ O(nlogn)
/// bad sides : requires additional memory ~ O(n) ,not adaptive ( when elements are nearly sorted,
/// the difficulty is still O(nlogn) )

void merge(int *arr, int left, int right) {

	int * Copy = new int[left + right];

	/// indexes of the first half , second and copied
	int l_index = 0, r_index = left, c_index = 0;


	while (l_index < left && r_index < left + right)
		Copy[c_index++] = (arr[l_index] < arr[r_index]) ? arr[l_index++] : arr[r_index++];

	while (l_index < left)
		Copy[c_index++] = arr[l_index++];

	while (r_index < left + right)
		Copy[c_index++] = arr[r_index++];

	memcpy(arr, Copy, sizeof(int)*(left + right));

	delete[] Copy;
};


void MergeSort(int* arr, int size) {

	if (size == 1)
		return;

	if (size == 2) {

		if (*arr > *(arr + 1)) {
			Swap(*arr, *(arr + 1));
		}
		return;
	}

	int mid = size / 2;

	MergeSort(arr, mid);
	MergeSort(arr + mid, size - mid);

	merge(arr, mid, size - mid);

}

///Quick Sort
/// good sides : maybe the fastest one in average case : O(nlogn) , 
/// additional memory for recursion calls
/// bad sides: worst case : O(n^2) , NOT STABLE

void QuickSort(int* arr, int size) {

	if (size == 1)
		return;

	if (size == 2) {
		if (*arr > *(arr + 1)) {
			Swap(*arr, *(arr + 1));
			return;
		}
	}


	int left = 0, right = size - 1;

	//not the smartest way to choose the pivot element
	int pivot = arr[size / 2];



	while (left <= right) {

		while (arr[left] < pivot) left++;
		while (arr[right] > pivot) right--;

		if (left <= right) {
			Swap(arr[left], arr[right]);
			left++;
			right--;
		}

	}

	if (left < size)
		QuickSort(arr + left, size - left);

	if (right > 0)
		QuickSort(arr, right + 1);

}

///Heapsort 
///good sides : O(nlogn) difficulty in every case,
///no additional memory needed
///bad sides : not stable


void sift(int* arr, int pos, int size) {

	int MovedElem = arr[pos];
	int MovedIndex = pos;
	int ChildIndex = pos + pos;

	while (ChildIndex < size) {

		if (ChildIndex < size - 1 && arr[ChildIndex] < arr[ChildIndex + 1])
			ChildIndex++;

		if (MovedElem > arr[ChildIndex])
			break;
		
		arr[MovedIndex] = arr[ChildIndex];

		MovedIndex = ChildIndex;
		ChildIndex *= 2;

	}

	arr[MovedIndex] = MovedElem;
}


void HeapSort(int* arr, int size) {

	//building the heap
	for (int i = size / 2 + 1; i > 1; i--)
		sift(arr, i-1, size);

	//swapping the first elem with the last
	//then restore the heap
	for (int i = size -1 ; i > 1; i--) {
		Swap(arr[1], arr[i]);
		sift(arr, 1, i );
	}

}




int main() {

	int arr[12] = { -124,5, 11, 2, 6, 7 , 42 , 13 , 88 , 21 ,9 , 8 };

	//QuickSort(arr1, 11);

	HeapSort(arr, 12);

	return 0;
}