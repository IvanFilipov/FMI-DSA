#include<stdio.h>

const int SIZE = 6;

typedef unsigned int _type_data;
typedef struct { //without this typedef we will have to write struct
				 //keyword everywhere when we use Elem
	int key;

	//no matter what data we got here
	_type_data data;

}Elem;

//given set
Elem elems[] = { 
	{ 10,20 },
	{ 30,14 },
	{ -5,14 },
	{ 77,347 },
	{ 24,81 },
	{ 11, 15 }
}; 

//this pointer to function typedef saves the day
typedef int(*Cmptor) (const Elem*, const Elem*);

//ordinary function
int myLess(const Elem* lhs, const Elem* rhs) {

	if (lhs->key < rhs->key)
		return 1;

	if (lhs->key == rhs->key)
		return 0;

	if (lhs->key > rhs->key)
		return -1;


}

int myGreater(const Elem* lhs, const Elem* rhs) {

	if (lhs->key > rhs->key)
		return 1;

	if (lhs->key == rhs->key)
		return 0;

	if (lhs->key < rhs->key)
		return -1;

}

//valid only for bit copyable structures
//we got shallow copy here
void swap(Elem* lhs, Elem* rhs) {

	Elem temp = *lhs;

	*lhs = *rhs;

	*rhs = temp;
}


//if we don't have the typedef  Cmptor func  -> bool (*func)(const Elem*,const Elem*)
void insertionSort(Elem *arr, int size,Cmptor func) {

	for (int i = 1; i < size; i++)
		for (int j = i; j > 0; j--)
			if(func(&arr[j] , &arr[j - 1]) == 1) // without typedef ->
				swap(&arr[j] , &arr[j - 1]);      //(*func)(...args) to invoke the function

}



void printElems() {

	for (int i = 0; i < SIZE; i++)
		printf("{ key : %d , data : %d } ", elems[i].key, elems[i].data);

	printf("\n\n");

}



int main() {

	
	printf("given elements :\n");
	printElems();
	printf("\n\n\n");


	printf("sorted by MyGreater :\n");
	insertionSort(elems, SIZE, myGreater);
	printElems();
	printf("\n\n\n");

	printf("sorted by MyLess :\n");
	insertionSort(elems, SIZE, myLess);
	printElems();
	printf("\n\n\n");

	return 0;
}