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

	size_t CurSize;
	node * pHead;

public:

	//the big four
	DynamicStack();
	DynamicStack(const DynamicStack&);
	DynamicStack& operator=(const DynamicStack&);
	~DynamicStack();

	//help functions
private:

	void CopyFrom(const DynamicStack&);
	void Clean();

	//interface
public:

	//letting us to 'see' the top or to 'adjust' it
	T& peek();
	const T& peek()const;

	//remove / add top element
	void push(const T&);
	void pop();

	bool isEmpty()const;
	size_t GetSize()const;

};

//THE BIG FOUR

template<class T>
DynamicStack<T>::DynamicStack() : CurSize(0), pHead(nullptr){

	/*...*/
};

template<class T>
DynamicStack<T>::~DynamicStack(){

	Clean();
}

template<class T>
DynamicStack<T>::DynamicStack(const DynamicStack<T>& other) :CurSize(0), pHead(nullptr){

	CopyFrom(other);
};

template<class T>
DynamicStack<T>& DynamicStack<T>::operator=(const DynamicStack<T>& other){

	if (this != &other){

		Clean();
		CopyFrom(other);

	}

	return *this;
}

template<class T>
void DynamicStack<T>::CopyFrom(const DynamicStack<T>& other){

	if (other.isEmpty())
		return;

	try{
		pHead = new node(other.pHead->data);
		
		//pHead->pNext = nullptr;

		node * ours = pHead;
		node* theirs = other.pHead->pNext;

		while (theirs != nullptr){

			ours->pNext = new node(theirs->data);
			
			ours = ours->pNext;
			theirs = theirs->pNext;

		}

		CurSize = other.CurSize;
	}
	catch (std::bad_alloc&){

		Clean();
		throw;
	}
}


template<class T>
void DynamicStack<T>::Clean(){

	node* temp;

	while (pHead != nullptr){

		temp = pHead;
		pHead = pHead->pNext;
		delete temp;
	}


	CurSize = 0;

}

template<class T>
void DynamicStack<T>::push(const T& elem){


	node* newElem = new node(elem,pHead);

	pHead = newElem;

	CurSize++;
}

template<class T>
void DynamicStack<T>::pop(){

	if (isEmpty())
		throw std::exception("the stack is empty !");

	node* temp = pHead;

	pHead = pHead->pNext;

	delete temp;

	CurSize--;

}


template<class T>
bool DynamicStack<T>::isEmpty()const{

	return CurSize == 0;
}

template<class T>
T& DynamicStack<T>::peek(){

	if (isEmpty()){
		throw std::exception("the stack is empty");
	}

	return pHead->data;
}

template<class T>
const T& DynamicStack<T>::peek()const{

	if (isEmpty()){
		throw std::exception("the stack is empty");
	}

	return pHead->data;

}

template<class T>
size_t DynamicStack<T>::GetSize()const{

	return CurSize;
}
