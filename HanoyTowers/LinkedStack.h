#include<iostream>

template<class T>
class LinkedStack {

private:

	struct node {

		T data;
		node * pNext;

		node(T _data, node* _pNext = nullptr) {

			data = _data;
			pNext = _pNext;

		}

		node() :pNext(nullptr){
			///
		}

	};

	size_t CurSize;
	node * pHead;

public:

	//the big four
	LinkedStack();
	LinkedStack(const LinkedStack&);
	LinkedStack& operator=(const LinkedStack&);
	~LinkedStack();

	//help functions
private:

	void CopyFrom(const LinkedStack&);
	void Clean();

	//interface
public:

	void push(const T&);
	void pop();

	bool isEmpty()const;
	T& peek();
	const T& peek()const;
	size_t getSize()const;

	void Print()const;



};

//THE BIG FOUR

template<class T>
LinkedStack<T>::LinkedStack() : CurSize(0), pHead(nullptr) {

	/*...*/
};

template<class T>
LinkedStack<T>::~LinkedStack() {

	Clean();
}

template<class T>
LinkedStack<T>::LinkedStack(const LinkedStack<T>& other) :CurSize(0), pHead(nullptr) {

	CopyFrom(other);
};

template<class T>
LinkedStack<T>& LinkedStack<T>::operator=(const LinkedStack<T>& other) {

	if (this != &other) {

		Clean();
		CopyFrom(other);

	}

	return *this;
}


//HELP FUNCTIONS


template<class T>
void LinkedStack<T>::CopyFrom(const LinkedStack<T>& other) {

	if (other.isEmpty())
		return;

	try {
		pHead = new node;
		pHead->data = other.pHead->data;
		pHead->pNext = nullptr;

		node * ours = pHead;
		node* theirs = other.pHead->pNext;

		while (theirs != nullptr) {

			ours->pNext = new node;
			ours = ours->pNext;
			ours->data = theirs->data;
			ours->pNext = nullptr;
			theirs = theirs->pNext;

		}

		CurSize = other.CurSize;
	}
	catch (std::bad_alloc&) {

		Clean();

		throw;
	}
}


template<class T>
void LinkedStack<T>::Clean() {

	node* temp;

	while (pHead != nullptr) {

		temp = pHead;
		pHead = pHead->pNext;
		delete temp;
	}


	CurSize = 0;

}

//INTERFACE
template<class T>
void LinkedStack<T>::push(const T& elem) {


	node * newElem = new node;
	newElem->data = elem;
	newElem->pNext = pHead;

	pHead = newElem;

	CurSize++;
}

template<class T>
void LinkedStack<T>::pop() {

	if (isEmpty())
		throw std::exception("the stack is empty !");

	node* temp = pHead;

	pHead = pHead->pNext;

	delete temp;

	CurSize--;

}


template<class T>
bool LinkedStack<T>::isEmpty()const {

	return CurSize == 0;
}

template<class T>
T& LinkedStack<T>::peek() {

	if (isEmpty()) {
		throw std::exception("the stack is empty");
	}

	return pHead->data;
}

template<class T>
const T& LinkedStack<T>::peek()const {

	if (isEmpty()) {
		throw std::exception("the stack is empty");
	}

	return pHead->data;

}

template<class T>
size_t LinkedStack<T>::getSize()const {

	return CurSize;
}


template<class T>
void LinkedStack<T>::Print()const {

	node* It = pHead;

	while (It != nullptr) {

		std::cout << It->data << std::endl;
		It = It->pNext;

	}

}
