#include<iostream>

template<class T>
class Queue{

private:

	//helping structure which presents each box
	struct node{
		T data;
		node* pNext;

		//ctor for node elements
		node(const T& _data, node* _pNext = nullptr){
			data = _data;
			pNext = _pNext;
		}

	};

	size_t CurSize;
	node* pFront;
	node* pRear;


public:

	//BIG FOUR
	Queue();
	Queue(const Queue&);
	Queue& operator=(const Queue&);
	~Queue();

private:

	//HELP FUNCTIONS
	void CopyFrom(const Queue&);
	void Clean();

public:

	//INTERFACE

	//getters / setters
	T& Front();
	const T& Front()const;

	T& Back();
	const T& Back() const;

	//add / remove
	void Enqueue(const T&);
	void Dequeue();

	bool isEmpty()const;
	size_t GetSize()const;

};

template<class T>
Queue<T>::Queue() :pFront(nullptr), pRear(nullptr), CurSize(0){

	/*...*/
}

template<class T>
Queue<T>::Queue(const Queue<T>& other):pFront(nullptr),pRear(nullptr),CurSize(0){

	CopyFrom(other);

}

template<class T>
Queue<T>& Queue<T>::operator=(const Queue<T>& other){

	if (this != &other){
          
		Clean();
		CopyFrom(other);

	}

	return *this;
}

template<class T>
Queue<T>::~Queue(){

	Clean();
}

template<class T>
void Queue<T>::Clean(){

	//iterating trough all elements
	node * destroyer ;


	while (pFront != nullptr){

		//taking the first one
		destroyer = pFront;
		
		//setting the new first one to the one linked with the old first one
		pFront = pFront->pNext;

		//the one pointer by destroyer will be deleted
		delete destroyer;
	}

	pRear = nullptr;
	pFront = nullptr;
	CurSize = 0;

}

template<class T>
void Queue<T>::CopyFrom(const Queue<T>& other){

	if (other.isEmpty())
		return;

	try{
		pFront = new node(other.pFront->data);

		node* ToCopy = other.pFront;
		node* copier = pFront;

		while (ToCopy->pNext != 0){

			ToCopy = ToCopy->pNext;

			copier->pNext = new node(ToCopy->data);
			copier = copier->pNext;

		}

		pRear = copier;
		CurSize = other.CurSize;
	}
	catch (std::bad_alloc &){

		Clean();
		throw;
	}


}

template<class T>
void Queue<T>::Enqueue(const T& _data){

	if (isEmpty()){

		pFront = new node(_data);
		pRear = pFront;
		CurSize++;
		return;
	}

	node* nElem = new node(_data);

	pRear->pNext = nElem;
	pRear = pRear->pNext;
	CurSize++;

}

template<class T>
void Queue<T>::Dequeue(){

	if (isEmpty())
		throw std::logic_error("empty queue!");
	

	node* destroyer = pFront;

	pFront = pFront->pNext;

	delete destroyer;
	CurSize--;
}


template<class T>
T& Queue<T>::Front(){

     if(isEmpty())
		 throw std::logic_error("empty queue!");

	return pFront ->data;
}

template<class T>
const T& Queue<T>::Front() const{

	if(isEmpty())
		throw std::logic_error("empty queue!");
	 
	return pFront->data;
}

template<class T>
T& Queue<T>::Back(){

	if(isEmpty())
		throw std::logic_error("empty queue!");
	 
	return pRear->data;
}

template<class T>
const T& Queue<T>::Back()const{

	if(isEmpty())
		throw std::logic_error("empty!");
	 
	return pRear->data;
}

template<class T>
bool Queue<T>::isEmpty()const{

	return CurSize == 0;
}

template<class T>
size_t Queue<T>::GetSize()const{

	return CurSize;
}
