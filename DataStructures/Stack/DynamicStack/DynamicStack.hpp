#include<iostream>

template<class T>
class DynamicStack{

private:

	struct node{

		T data;
		node * pNext;

		node(T _data, node* _pNext = nullptr) {

			data = _data;
			pNext = _pNext;

		}
	};

	size_t curSize;
	node * pTop;

public:

	//the big four
	DynamicStack();
	DynamicStack(const DynamicStack&);
	DynamicStack& operator=(const DynamicStack&);
	~DynamicStack();

	//help functions
private:

	void copyFrom(const DynamicStack&);
	void clean();

	//interface
public:

	//letting us to 'see' the top or to 'adjust' it
	T& peek();
	const T& peek()const;

	//remove / add top element
	void push(const T&);
	void pop();

	bool isEmpty()const;
	size_t getSize()const;

};

//THE BIG FOUR

template<class T>
DynamicStack<T>::DynamicStack() : curSize(0), pTop(nullptr){

	/*...*/
};

template<class T>
DynamicStack<T>::~DynamicStack(){

	clean();
}

template<class T>
DynamicStack<T>::DynamicStack(const DynamicStack<T>& other) :curSize(0), pTop(nullptr){

	copyFrom(other);
};

template<class T>
DynamicStack<T>& DynamicStack<T>::operator=(const DynamicStack<T>& other){

	if (this != &other){

		clean();
		copyFrom(other);

	}

	return *this;
}

template<class T>
void DynamicStack<T>::copyFrom(const DynamicStack<T>& other){

	if (other.isEmpty())
		return;

	try{
		pTop = new node(other.pTop->data);
		
		//pTop->pNext = nullptr;

		node* ours = pTop;
		node* theirs = other.pTop->pNext;

		while (theirs != nullptr){

			ours->pNext = new node(theirs->data);
			
			ours = ours->pNext;
			theirs = theirs->pNext;

		}

		curSize = other.curSize;
	}
	catch (std::bad_alloc&){

		clean();
		throw;
	}

}


template<class T>
void DynamicStack<T>::clean(){

	node* temp;

	while (pTop != nullptr){

		temp = pTop;
		pTop = pTop->pNext;
		delete temp;
	}


	curSize = 0;

}

template<class T>
void DynamicStack<T>::push(const T& elem){


	node* newElem = new node(elem,pTop);

	pTop = newElem;

	curSize++;
}

template<class T>
void DynamicStack<T>::pop(){

	if (isEmpty())
		throw std::exception("the stack is empty !");

	node* temp = pTop;

	pTop = pTop->pNext;

	delete temp;

	curSize--;

}


template<class T>
bool DynamicStack<T>::isEmpty()const{

	return curSize == 0;
}

template<class T>
T& DynamicStack<T>::peek(){

	if (isEmpty()){
		throw std::logic_error("the stack is empty");
	}

	return pTop->data;
}

template<class T>
const T& DynamicStack<T>::peek()const{

	if (isEmpty()){
		throw std::exception("the stack is empty");
	}

	return pTop->data;

}

template<class T>
size_t DynamicStack<T>::getSize()const{

	return curSize;
}
