/*
 * Some tests for our custom BST.
 * This file is part of the "Data structures and algorithms" course. FMI 2018/19
 *
 * Author : Ivan Filipov	
 */

#pragma once

// some constants, change them to customize the tests
const unsigned int NELEM     = 16;  // how many elements to insert in our tree
const unsigned int MAX_KEY   = 51;  // the max value a key can have
const unsigned int MAX_DATA  = 101; // max data value is [-100;100]
const unsigned int NTRY      = 4;   // numbers of tries

// a forward declaration of the custom BST class
class bs_tree;

// test functions : 
// run a fixed tree test
void run_basic_tests();
// run a randomized tree test
void run_advanced_tests();
