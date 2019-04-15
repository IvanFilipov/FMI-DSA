/*******************************************************************************
 * This file is part of the "Data structures and algorithms" course. FMI 2018/19 
 *******************************************************************************/

/**
 * @file   static_stack.c
 * @author Ivan Filipov
 * @date   10.2018
 * @brief  A simple linear data structure - stack. 
 *         Implemented in plain C as an array adapter.
 * @see https://en.wikipedia.org/wiki/Stack_(abstract_data_type)
 */
 
#include <stdio.h> // fprintf()

#include "static_stack.h" // our stack declarations

void stack_init(stack* const context) {
	
	context->top = 0;
	for (int i = 0; i < MAX_SSIZE; i++)
		context->data[i] = 0;
}

int stack_is_empty(const stack* const context) {
	
	return context->top == 0;
}
	
void stack_push(stack* const context, data_type el) {
	
	if (context->top == MAX_SSIZE)
		fprintf(stderr, "not enough space in the stack!");
	else
		context->data[context->top++] = el;
}

data_type stack_pop(stack* const context) {
	
	if (stack_is_empty(context)) {
		fprintf(stderr, "empty stack!");
		return 0;
	}

	return context->data[--context->top];
}
