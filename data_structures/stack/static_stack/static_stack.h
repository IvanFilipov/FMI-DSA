/*
 * A simple linear data structure - stack. Implementation in plain C, an array adapter.
 * This file is part of the "Data structures and algorithms" course. FMI 2018/19
 *
 * Author : Ivan Filipov	
 */
#pragma once

#define MAX_SSIZE 100

typedef int data_type;

/* stack data structure representation */
typedef struct {
	
	data_type data[MAX_SSIZE]; 
	int top;
} stack;


/* Stack initialization. All elements are set to be zeros */
void stack_init(stack* const context);

/* Check if a stack is empty. Returns 1 if empty */
int stack_is_empty(const stack* const context);
	
/* Add new element on the top of the stack */
void stack_push(stack* const context, data_type el);

/* Remove the top element, return its value */
data_type stack_pop(stack* const context);
