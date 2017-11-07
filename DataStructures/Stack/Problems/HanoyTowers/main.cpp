// used algorithm : https://en.wikipedia.org/wiki/Tower_of_Hanoi - Recursive solution 
					

#include"DynamicStack.hpp"

typedef DynamicStack<int> tower;


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

	//numbers will represent the disk's sizes 
	for (int i = 4; i > 0; --i)
		A.push(i);

	
	//starting position
	//{1}  {} {}
	//{2}  {} {}
	//{3}  {} {}
 	//{4}  {} {}

	HanoySolve(A, C, B, A.GetSize());

	//C.Print()
	while (!C.isEmpty()) {

		std::cout << C.peek() << ' ';
		C.pop();

	}
	//end position
	//{}  {} {1}
	//{}  {} {2}
	//{}  {} {3}
	//{}  {} {4}

	return 0;
}