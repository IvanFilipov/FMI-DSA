/*
 * A simple linear data structure - stack. Implementation in plain C, an array adapter.
 * This file is part of the "Data structures and algorithms" course. FMI 2018/19
 *
 * Author : Ivan Filipov	
 */
#include <stdio.h>
#include "static_stack.h"

void stack_init(stack* const context) {
	
	context->top = 0;
	for(int i = 0; i < MAX_SSIZE; i++)
		context->data[i] = 0;
}

int stack_is_empty(const stack* const context) {
	
	return context->top == 0;
}
	
/* Add new element on the top of the stack */
void stack_push(stack* const context, data_type el) {
	
	if (context->top == MAX_SSIZE)
		fprintf(stderr, "not enough space in the stack!");
	else
		context->data[context->top++] = el;
}

/* Remove the top element, return its value */
data_type stack_pop(stack* const context) {
	
	if (stack_is_empty(context)) {

		fprintf(stderr, "empty stack!");
		return 0;
	}

	return context->data[--context->top];
}
