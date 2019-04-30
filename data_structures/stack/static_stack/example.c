/*******************************************************************************
 * This file is part of the "Data structures and algorithms" course. FMI 2018/19 
 *******************************************************************************/

/**
 * @file   example.c
 * @author Ivan Filipov
 * @date   10.2018
 * @brief  Example usage of our C-style stack data structure.
 * @see https://en.wikipedia.org/wiki/Stack_(abstract_data_type)
 */

#include <stdio.h> // fprintf()

#include "static_stack.h" // our stack declarations

/// how many input from user to be read
#define N_INPUTS 5

int main() {
	// create the stack
	stack s;
	stack_init(&s);
	/* alternative :
	stack s = {};
	*/
	// push some elements
	data_type el;
	int cnt = N_INPUTS;
	printf("please, enter %d elements :\n", N_INPUTS);
	do {
		scanf("%d", &el);
		if (el > 1000) el = el % 1000;
		stack_push(&s, el);
	} while (--cnt);
	// nicely output the elements using pop() 
	printf("\nthe stack looks like :\n");
	while (!stack_is_empty(&s))
		printf("\n|%3d|\n|___|", stack_pop(&s));
	putchar('\n');
	
	return 0;
}
