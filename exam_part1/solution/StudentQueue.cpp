#pragma once

#include "StudentQueue.h"

StudentQueue::StudentQueue() :pHead(nullptr), pTail(nullptr) {

	/*...*/
}

StudentQueue::StudentQueue(const StudentQueue& other) : pHead(nullptr), pTail(nullptr) {

	copyFrom(other);

}

StudentQueue& StudentQueue::operator=(const StudentQueue& other) {

	if (this != &other) {

		clean();
		copyFrom(other);

	}

	return *this;
}

StudentQueue::~StudentQueue() {

	clean();
}


void StudentQueue::clean() {

	//iterating trough all elements
	node * destroyer;


	while (pHead != nullptr) {

		//taking the first one
		destroyer = pHead;

		//setting the new first one to the one linked with the old first one
		pHead = pHead->pNext;

		//the one pointed by destroyer will be deleted
		delete destroyer;
	}

	pTail = nullptr;
	pHead = nullptr;

}


void StudentQueue::copyFrom(const StudentQueue& other) {

	if (other.isEmpty())
		return;

	//if there is a problem with one of the memory
	//allocations, we should take care for all
	//memory which was allocated successfully
	try {
		pHead = new node(other.pHead->st);

		node* ToCopy = other.pHead;
		node* copier = pHead;

		while (ToCopy->pNext != 0) {

			ToCopy = ToCopy->pNext;

			copier->pNext = new node(ToCopy->st);
			copier = copier->pNext;

		}

		pTail = copier;
	}
	catch (std::bad_alloc&) {

		clean();
		throw;
	}
}

void StudentQueue::enqueue(const Student& newStudent) {

	if (isEmpty()) {

		pHead = new node(newStudent);
		pTail = pHead;
		return;
	}

	//the new node to add
	node* nElem = new node(newStudent);

	//simple 'fast' iterating pointer
	node* it = pHead;

	//searching for group member
	while (it != pTail && it->st.groupId != nElem->st.groupId)
		it = it->pNext;

	//the slow pointer 
	node* lastSeenMember = nullptr;

	//skipping all members of the same group as new elem's
	while (it != pTail && it->st.groupId == nElem->st.groupId) {

		lastSeenMember = it;
		it = it->pNext;
	}

	//if there aren't any friends of new elem's
	//or the last queue members are those friends
	//then we have just push back operation
	if (it == pTail && lastSeenMember == nullptr) {

		pTail->pNext = nElem;
		pTail = pTail->pNext;
		return;
	}

	//if there are students from the same group
	//preforming insert after operation
	node* tmp = lastSeenMember->pNext;

	lastSeenMember->pNext = nElem;
	nElem->pNext = tmp;

}

void StudentQueue::dequeue() {

	if (isEmpty())
		throw std::logic_error("empty queue!");


	node* destroyer = pHead;

	pHead = pHead->pNext;

	delete destroyer;
}



Student& StudentQueue::front() {

	if (isEmpty())
		throw std::logic_error("empty queue!");

	return pHead->st;
}

const Student& StudentQueue::front() const {

	if (isEmpty())
		throw std::logic_error("empty queue!");

	return pHead->st;
}

bool StudentQueue::isEmpty()const {

	return pHead == nullptr;
}
