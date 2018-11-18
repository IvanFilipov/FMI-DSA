/*
 * An example about usage of comparator function with sorting algorithms. C style. 
 * This file is part of the "Data structures and algorithms" course. FMI 2018/19
 *
 * Author : Ivan Filipov	
 */
 
#include<stdio.h> // printf()

typedef unsigned int _type_data;
typedef struct { // without this typedef we will have to write struct
				      // keyword everywhere when we use Elem
	int        key;   // the key used for comparing
	_type_data data;  // no matter what data we got here
} elem;

const int ELMS_COUNT = 6;

//given set
elem elems[] = { 
	{ 10, 20 },
	{ 30, 14 },
	{ -5, 14 },
	{ 77, 34 },
	{ 24, 81 },
	{ 11, 15 }
}; 

// this pointer to function typedef saves the day
// without it the syntax is pretty bad
// read as cmp_fptr is a pointer to function taking two elems and returning int
typedef int(*cmp_fptr) (const elem*, const elem*);

// ordinary function for comparing two elems
// returns >0 if lhs < rhs
//         0  if equal
//         <0 if lhs > rhs
int less(const elem* lhs, const elem* rhs) {

	if (lhs->key < rhs->key)
		return 1;
	if (lhs->key == rhs->key)
		return 0;
	if (lhs->key > rhs->key)
		return -1;
}

int greater(const elem* lhs, const elem* rhs) {

	if (lhs->key > rhs->key)
		return 1;
	if (lhs->key == rhs->key)
		return 0;
	if (lhs->key < rhs->key)
		return -1;
}

// valid only for bit copyable structures
// we got shallow copy here
void swap(elem* lhs, elem* rhs) {

	elem temp = *lhs;
	*lhs = *rhs;
	*rhs = temp;
}
// insertion sort with additional argument - a pointer to comparator function
void insertion_sort(elem* arr, int size, cmp_fptr cmp) {

	for (int i = 1; i < size; i++)
		for (int j = i; j > 0; j--)
			if (cmp(&arr[j] , &arr[j - 1]) > 0) // slight difference is here
				swap(&arr[j] , &arr[j - 1]);
}
// simple output function
void print_elems() {

	for (int i = 0; i < ELMS_COUNT; i++)
		printf("{ key : %d , data : %d } ", elems[i].key, elems[i].data);
	printf("\n\n");
}

int main() {
	
	printf("given elements :\n");
	print_elems();
	
	printf("sorted with \"grater\" :\n");
	insertion_sort(elems, ELMS_COUNT, greater);
	print_elems();
	
	printf("sorted with \"less\" :\n");
	insertion_sort(elems, ELMS_COUNT, less);
	print_elems();
	
	return 0;
}
