// used algorithm : https://en.wikipedia.org/wiki/Tower_of_Hanoi - Recursive solution 
					

#include"LinkedStack.h"

typedef LinkedStack<int> tower;


void Move(tower& src, tower& des) {

	des.push(src.peek());
	src.pop();

}

void HanoySolve(tower& A , tower& C,tower& B , int step ) {
	
	if (step == 1)
		Move(A, C);
	else {

		HanoySolve(A, B, C ,step -1);

		Move(A, C);

		HanoySolve(B, C, A,step -1);

	}


}


int main() {


	tower A, B, C;

	for (int i = 4; i > 0; --i) {

		A.push(i);
	}

	HanoySolve(A, C, B, A.getSize());

	C.Print();

	return 0;
}