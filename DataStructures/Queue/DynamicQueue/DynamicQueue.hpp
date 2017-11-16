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

	size_t curSize;
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
	void copyFrom(const Queue&);
	void clean();

public:

	//INTERFACE

	//getters / setters
	T& front();
	const T& front()const;

	T& back();
	const T& back() const;

	//add / remove
	void enqueue(const T&);
	void dequeue();

	bool isEmpty()const;
	size_t getSize()const;

};

template<class T>
Queue<T>::Queue() :pFront(nullptr), pRear(nullptr), curSize(0){

	/*...*/
}

template<class T>
Queue<T>::Queue(const Queue<T>& other):pFront(nullptr),pRear(nullptr),curSize(0){

	copyFrom(other);

}

template<class T>
Queue<T>& Queue<T>::operator=(const Queue<T>& other){

	if (this != &other){
          
		clean();
		copyFrom(other);

	}

	return *this;
}

template<class T>
Queue<T>::~Queue(){

	clean();
}

template<class T>
void Queue<T>::clean(){

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
	curSize = 0;

}

template<class T>
void Queue<T>::copyFrom(const Queue<T>& other){

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
		curSize = other.curSize;
	}
	catch (std::bad_alloc &){

		clean();
		throw;
	}


}

template<class T>
void Queue<T>::enqueue(const T& _data){

	if (isEmpty()){

		pFront = new node(_data);
		pRear = pFront;
		curSize++;
		return;
	}

	node* nElem = new node(_data);

	pRear->pNext = nElem;
	pRear = pRear->pNext;
	curSize++;

}

template<class T>
void Queue<T>::dequeue(){

	if (isEmpty())
		throw std::logic_error("empty queue!");
	

	node* destroyer = pFront;

	pFront = pFront->pNext;

	delete destroyer;
	curSize--;
}


template<class T>
T& Queue<T>::front(){

     if(isEmpty())
		 throw std::logic_error("empty queue!");

	return pFront->data;
}

template<class T>
const T& Queue<T>::front() const{

	if(isEmpty())
		throw std::logic_error("empty queue!");
	 
	return pFront->data;
}

template<class T>
T& Queue<T>::back(){

	if(isEmpty())
		throw std::logic_error("empty queue!");
	 
	return pRear->data;
}

template<class T>
const T& Queue<T>::back()const{

	if(isEmpty())
		throw std::logic_error("empty!");
	 
	return pRear->data;
}

template<class T>
bool Queue<T>::isEmpty()const{

	return curSize == 0;
}

template<class T>
size_t Queue<T>::getSize()const{

	return curSize;
}
