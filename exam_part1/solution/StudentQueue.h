#pragma once

#include<string>


//student data + the time he enters the queue
struct Student{

	std::string name;
	int groupId;

	unsigned int enqTime;

	//C++ 11 way to forbid compile-generated copy constructor and operator=
	Student& operator=(const Student&) = delete;
	Student(const Student&) = delete;
	Student() = default;

	//C++ 98 way is to declare them as 'private'

};


//implementation on list
/*
 
 pHead                                  pTail
   |                                     |
   v                      		 v
   __      __       __      __           __
  |__| -> |__| ->  |__| -> |__| .... -> |__| -> NULL 
 

*/

class StudentQueue {

private:

	//helping structure representing each box
	struct node {

		Student st;
		node* pNext;

		node(const Student& other, node* _pNext = nullptr) {

			st.name = other.name;
			st.groupId = other.groupId;
			st.enqTime = other.enqTime;
			pNext = _pNext;
		}

	};

	node* pHead;
	node* pTail;


public:

	StudentQueue();
	StudentQueue(const StudentQueue&);
	StudentQueue& operator=(const StudentQueue&);
	~StudentQueue();

private:

	//HELP FUNCTIONS
	void copyFrom(const StudentQueue&);
	void clean();

public:

	//getter for the element in the beginning of the queue 
	Student& front();
	const Student& front()const;

	//add
	void enqueue(const Student&);
	//remove
	void dequeue();

	bool isEmpty()const;

};



