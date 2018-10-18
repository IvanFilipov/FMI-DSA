#pragma once

#include "BST.h"

#include<stdlib.h> //rand , srand
#include<time.h> //time

#include<stdexcept> //std::exception

const unsigned int NELEM = 16; //how many elements to insert in our tree
const unsigned int MAX_KEY = 51; //the max value a key can have
const unsigned int MAX_DATA = 101; // max data value is [-100;100]
const unsigned int NTRY = 4; //numbers of tries

void init(BST&);

void searchTest(const BST&);

void removeTest(BST&);

void runBasicTests(BST&);

void runAdvancedTests(BST&);