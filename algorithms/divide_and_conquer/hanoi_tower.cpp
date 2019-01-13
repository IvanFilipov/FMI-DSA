/*******************************************************************************
 * This file is part of the "Data structures and algorithms" course. FMI 2018/19 
 *******************************************************************************/

/**
 * @file   hanoi_tower.cpp
 * @author Ivan Filipov
 * @date   01.2019
 * @brief  A solution to Hanoi tower's task.
 *         Using a recursive "divide and conquer" algorithm. 
 * @see https://en.wikipedia.org/wiki/Tower_of_Hanoi
 */

#include <iostream> // std::cout
#include <stack>    // std::stack

/// each tower is a stack of numbers
typedef std::stack<int> tower;
/// the three towers
tower At, Bt, Ct;
/// how many elements in each tower
const int ECOUNT = 4; 

/// make a step, moving the top disk from one tower to another
/// @param[in,out] src: tower from which to remove the disk
/// @param[in,out] des: tower to which to add the disk 
void move(tower& src, tower& des) {

	des.push(src.top());
	src.pop();
}

/// get the top element of a tower, with fixed size
/// @param[in] level: how much the tower size should be
/// @param[in,out] t: tower from which an element will be taken
/// @retval character of the number from the top of the tower,
///         if the tower doesn't meet the requirement for size
///         whitespace is returned
char char_from_tower(int level, tower& t) {
	
	char ret;
	if (t.size() == level) {
		ret = (t.top() + '0');
		t.pop();
	} else { 
		ret = ' ';
	}
	
	return ret;
}

/// simply outputs the current towers contain
/// @param[in] A: a copy of the first tower
/// @param[in] B: a copy of the second tower
/// @param[in] C: a copy of the third tower
/// @note copies are passed on purpose.
void print_current(tower A, tower B, tower C) {
	
	char a, b, c;
	std::cout << "current towers : \n";
	for(int i = ECOUNT; i > 0; i--) {
		a = char_from_tower(i, A);
		b = char_from_tower(i, B);
		c = char_from_tower(i, C);  
		std::cout << "| " << a << "| | " << b << "| | " << c << "|\n" 
	              << "|__| |__| |__|\n";
	}
}

/// the recursive algorithm for solving the problem
/// @param[in,out] A: a current first tower
/// @param[in,out] B: a current second tower
/// @param[in,out] C: a current third tower
/// @note on different steps of the algorithm the order of towers changes
void solve_Hanoi(tower& A, tower& C, tower& B, int step) {
	
	if (step == 1) {
		move(A, C);
		// using the global variables, due to correct order
		print_current(At, Bt, Ct); 
		return;
	}
	
	solve_Hanoi(A, B, C , step - 1);
	
	move(A, C);
	print_current(At, Bt, Ct);
	
	solve_Hanoi(B, C, A, step - 1);
}


int main() {
	
	/* initialize the first tower */
	for (int i = ECOUNT; i > 0; --i) {
		At.push(i);
	}
	print_current(At, Bt, Ct);
	
	/* run the algorithm */
	solve_Hanoi(At, Ct, Bt, At.size());
	
	/* output the results */
	std::cout << "\n\nresult in C \n";
	for(int i = Ct.size(); i > 0; i--) {
		std::cout << "| " << Ct.top() << "|\n"
	              << "|__|\n";
		Ct.pop();
	}

	return 0;
}
