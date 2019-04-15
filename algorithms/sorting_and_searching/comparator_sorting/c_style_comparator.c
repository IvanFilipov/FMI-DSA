/*******************************************************************************
 * This file is part of the "Data structures and algorithms" course. FMI 2018/19 
 *******************************************************************************/

/**
 * @file   c_style_comparator.c
 * @author Ivan Filipov
 * @date   12.2019
 * @brief  An example about usage of comparator function with sorting algorithms. C style. 
 */
 
#include <stdio.h> // printf()

typedef unsigned int _type_data; //!< type of "data" fields
/**
 * @struct elem
 * @brief  defines elements to be sorted
 *
 * @note without this typedef we will have to write struct
 *       keyword everywhere when we use Elem
 */
typedef struct { 
	int        key;   //!< the key used for comparing
	_type_data data;  //!< no matter what data we got here
} elem;

const int ELMS_COUNT = 6; //!< number of elements to be sorted

/// given set of elements to be sorted
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
/// pointer to compare function
typedef int(*cmp_fptr) (const elem*, const elem*);

/**
 * @brief Ordinary function for comparing two elements with (<)
 * @retval >0 if lhs < rhs
 * @retval 0  if equal
 * @retval <0 if lhs > rhs
 */
int less(const elem* lhs, const elem* rhs) {

	if (lhs->key < rhs->key)
		return 1;
	else if (lhs->key == rhs->key)
		return 0;
	else
		return -1;
}

/**
 * @brief Ordinary function for comparing two elements with (>)
 * @retval >0 if lhs < rhs
 * @retval 0  if equal
 * @retval <0 if lhs > rhs
 */
int greater(const elem* lhs, const elem* rhs) {

	if (lhs->key > rhs->key)
		return 1;
	else if (lhs->key == rhs->key)
		return 0;
	else
		return -1;
}

/**
 * @brief simple swap function
 *
 * @note valid only for bit copyable structures -
 *       we got shallow copy here
 */
void swap(elem* lhs, elem* rhs) {

	elem temp = *lhs;
	*lhs = *rhs;
	*rhs = temp;
}

/**
 * @brief insertion sort
 * @param[in] arr: array to be sorted
 * @param[in] size: size of the array
 * @param[in] cmp: pointer to comparator function, to be used 
 */
void insertion_sort(elem* arr, int size, cmp_fptr cmp) {

	for (int i = 1; i < size; i++)
		for (int j = i; j > 0; j--)
			if (cmp(&arr[j] , &arr[j - 1]) > 0) // the slight difference is here
				swap(&arr[j] , &arr[j - 1]);
}

/// simple output function
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
