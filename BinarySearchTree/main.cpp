#include"BST.h"

int main() {

	BST t;

	t.Insert(11,1);
	t.Insert(8,2);
	t.Insert(3,3);
	t.Insert(9, 4);
	t.Insert(1,5);
	t.Insert(5, 6);


	t.Insert(23, 7);
	t.Insert(16, 8);
	t.Insert(14, 9);
	t.Insert(20, 10);
	t.Insert(41,11 );
	t.Insert(55,12);
	t.Insert(58, 12);

	int a = 23;
	t.Remove(a);

	BST t1(t);

	DataType *c = t1.Search(16);

	DataType c1 = *c;



	return 0;

}