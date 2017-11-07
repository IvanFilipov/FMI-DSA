#include <iostream>

//simple Queue implementation ON array

template <typename T>
class Queue {

private:

	T* data;

	unsigned short front; // just indexes
	unsigned short rear;	 //where to add/remove

	bool isEmpty;
	size_t size;


public:

	//Big 4
	Queue(size_t);
	Queue(const Queue&);
	Queue& operator=(const Queue&);
	~Queue();

private:

	//help functions
	void CopyFrom(const Queue&);
	void Clean();

public:
	//interface

	void Enqueue(const T&);
	T Dequeue(); //a copy should be passed

	size_t GetNumElems()const;
};

template<typename T>
Queue<T>::Queue(size_t s) : data(nullptr),size(s),front(0),rear(0),isEmpty(true){
	
	data = new T[size];
	/*...*/

}


template<typename T>
Queue<T>::~Queue(){

	Clean();
}

template<typename T>
Queue<T>::Queue(const Queue<T>& other){

	CopyFrom(other);
}

template<typename T>
Queue<T>& Queue<T>::operator=(const Queue<T>& other){

	if (this != &other){

		Clean();
		CopyFrom(other);
	}

	return *this;
}


template<typename T>
void Queue<T>::Enqueue(const T& elem){

	//there is no space
	if ((rear == front) && !isEmpty)
		throw std::logic_error("the queue is FULL! \n");
	

	data[rear++] = elem;

	//makes the queue cyclic
	if (rear >= size)
		rear = 0;

	isEmpty = false;
}

template<typename T>
T Queue<T>::Dequeue(){
	if (isEmpty)
		throw std::logic_error("empty queue!");

	T elem;

	elem = data[front++];

	//makes the queue cyclic
	if (front >= size)
		front = 0;

	if (front == rear)
		isEmpty = true;

	return elem;

}

template<typename T>
size_t Queue<T>::GetNumElems() const{

	if (isEmpty)
		return 0;

	if (front == rear && !isEmpty)
		return size;

	size_t NumElems = 0;

	if (front > rear) { // we should make a new cycle
		
		NumElems += (size - front);
		NumElems += rear;
	}
	else
		NumElems += (rear - front);

	return NumElems;
}


template<typename T>
void Queue<T>::CopyFrom(const Queue<T>& other){

	size = other.size;

	data = new T[size];

	for (int i = 0; i < size; i++)
		data[i] = other.data[i];

	front = other.front;
	rear = other.rear;
	isEmpty = other.isEmpty;

}

template<class T>
void Queue<T>::Clean(){

	delete[] data;
	front = 0;
	rear = 0;
	isEmpty = true;
}


