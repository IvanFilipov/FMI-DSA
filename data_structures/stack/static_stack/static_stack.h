/*******************************************************************************
 * This file is part of the "Data structures and algorithms" course. FMI 2018/19 
 *******************************************************************************/

/**
 * @file   static_stack.h
 * @author Ivan Filipov
 * @date   10.2018
 * @brief  A simple linear data structure - stack. 
 *         Implemented in plain C as an array adapter.
 * @see https://en.wikipedia.org/wiki/Stack_(abstract_data_type)
 */

#pragma once

/// maximum count of elements in stack
#define MAX_SSIZE 100 

/// elements type
typedef int data_type; 

/** stack data structure representation */
typedef struct {
	data_type data[MAX_SSIZE]; //!< simple array chunk, in which the data will be stored
	int       top;             //!< a pointer to the top element
} stack;

// notice that in C we don't have "this" pointer, that is why
// our API gets "context" as an argument.

/** Stack initialization. All elements are set to be zeros */
void stack_init(stack* const context);

/** Check if a stack is empty. Returns 1 if empty */
int stack_is_empty(const stack* const context);
	
/** Add new element on the top of the stack */
void stack_push(stack* const context, data_type el);

/** Remove the top element, return its value */
data_type stack_pop(stack* const context);
