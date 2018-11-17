/*
 * Example usage of a C-style stack data structure.
 * This file is part of the "Data structures and algorithms" course. FMI 2018/19
 *
 * Author : Ivan Filipov	
 */

#include<stdio.h>
#include "static_stack.h"

#define N_INPUTS 5

int main() {
	// create the stack
	stack s = {};
	/* alternative :
	stack s;
	stack_init(&s);
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
