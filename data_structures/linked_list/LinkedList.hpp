#include<iostream>

template<class T>
class LinkedList {

private:

	struct node {

		T data;

		node* pNext;

		node(T _data, node* _pNext = nullptr) {

			data = _data;
			pNext = _pNext;

		}


	};

	node* pFront;
	node *pBack;
	int curSize;


public:

	//very basic forward iterator
	class Iterator {

	private:

		node* pNode;

	public:
		Iterator(Iterator& other) :pNode(other.pNode) {
			/*...*/
		}

		Iterator(node* n) : pNode(n) {

		}

	public:

		//No need for BIG4

		const T& operator*() const{
			return pNode->data;
		}

		T& operator*(){
			return pNode->data;
		}

		const T* operator->() const{
			return pNode->*data;
		}

		T* operator->(){
			return pNode->*data;
		}

		Iterator& operator++(){
			
			pNode = pNode->pNext;

			return *this;
		}

		Iterator operator++(int){

			Iterator res(*this);
			++(*this);
			return res;
		}

		bool operator==(const Iterator& other) const{
			return pNode == other.pNode;
		}

		bool operator!=(const Iterator& other) const{
			return !(other == *this);
		}

		bool operator<(const Iterator& other) const{
			return pNode->data < other.pNode->data;
		}

		bool operator>(const Iterator& other) const{
			return other.pNode->data < pNode->data;
		}

		node* eraseAfter() {

			if (pNode->pNext == nullptr)
				return nullptr;

			node* deleted = pNode->pNext;

			pNode->pNext = pNode->pNext->pNext;

			delete[]deleted;

			return pNode;

		}

		node* insertAfter(const T& elem) {

			if (pNode->pNext == nullptr) {

				pNode->pNext = new node(elem);
				return pNode->pNext;
			}

			node* newNode = new node(elem);

			newNode->pNext = pNode->pNext;

			pNode->pNext = newNode;

			return newNode;

		}


	};

	//the big four
public:

	LinkedList();
	LinkedList(const LinkedList&);
	LinkedList& operator=(const LinkedList&);
	~LinkedList();


	//help functions
private:

	void copyFrom(const LinkedList&);
	void clean();

	//interface
public:

	void pushBack(const T&);
	void pushFront(const T&);

	const T& back()const;
	const T& front()const;

	void popBack();
	void popFront();


	//TO DO


	void print()const;
	bool search(const T&)const;

	bool isEmpty()const;
	int getSize()const;

	Iterator insertAfter(Iterator it, const T& elem) {

		node* newElem = it.insertAfter(elem);

		if (it == Iterator(pBack)) {
			pBack = newElem;
		}

		return Iterator(newElem);

	}

	Iterator eraseAfter(Iterator it) {

		node * next = it.eraseAfter();

		if (next == nullptr)
			return end();
		else if (next->pNext == nullptr) {

			pBack = next;
			return Iterator(next);
		}
		else
			return Iterator(next->pNext);
	}
	Iterator begin() {

		return Iterator(pFront);

	}

	Iterator end() {

		return Iterator(pBack->pNext);
	}

};


template<class T>
LinkedList<T>::LinkedList() :pFront(nullptr), pBack(nullptr), curSize(0) {

	//...
}

template<class T>
LinkedList<T>::LinkedList(const LinkedList<T>& other) :pFront(nullptr), pBack(nullptr), curSize(0) {

	copyFrom(other);
}

template<class T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& other) {

	if (this != &other) {

		clean();
		copyFrom(other);

	}

	return *this;
}

template<class T>
LinkedList<T>::~LinkedList() {

	clean();
}


template<class T>
void LinkedList<T>::copyFrom(const LinkedList<T>& other) {

	if (other.isEmpty())
		return;

	try {

		pFront = new node(other.pFront->data);


		node* ToCopy = other.pFront;
		node* copier = pFront;

		while (ToCopy->pNext != nullptr) {

			ToCopy = ToCopy->pNext;

			copier->pNext = new node(ToCopy->data);
			copier = copier->pNext;

		}

		pBack = copier;

	}
	catch (std::bad_alloc&) {

		clean();
		throw;
	}

	curSize = other.curSize;

}

template<class T>
void LinkedList<T>::clean() {

	node* destroyer;

	while (pFront != nullptr) {

		destroyer = pFront;
		pFront = pFront->pNext;

		delete destroyer;

	}

	pFront = nullptr;
	pBack = nullptr;
	curSize = 0;
}


template<class T>
void LinkedList<T>::pushFront(const T& elem) {

	if (isEmpty()) {

		pFront = new node(elem);
		pBack = pFront;
		curSize++;
		return;

	}

	node* newElem = new node(elem);

	newElem->pNext = pFront;
	pFront = newElem;

	curSize++;


}

template<class T>
void LinkedList<T>::pushBack(const T& elem) {

	if (isEmpty()) {

		pFront = new node(elem);
		pBack = pFront;
		curSize++;
		return;

	}

	pBack->pNext = new node(elem);
	pBack = pBack->pNext;

	curSize++;


}

template<class T>
const T& LinkedList<T>::front()const {

	if (isEmpty())
		throw std::exception("the list is empty!");

	return pFront->data;

}

template<class T>
const T& LinkedList<T>::back()const {

	if (isEmpty())
		throw std::exception("the list is empty!");

	return pBack->data;

}

template<class T>
void LinkedList<T>::popFront() {

	if (isEmpty())
		throw std::exception("the list is empty!");

	node* destroyer = pFront;

	pFront = pFront->pNext;

	delete destroyer;

	curSize--;

}


template<class T>
void LinkedList<T>::popBack() {

	if (isEmpty())
		throw std::logic_error("the list is empty!");

	
	if(curSize == 1){
		
		delete pFront;
		
		pFront = nullptr;
		pBack = nullptr;
		curSize = 0;
		
	}
	
	
	node* destroyer = pFront;

	while (destroyer->pNext != pBack) {

		destroyer = destroyer->pNext;

	}

	delete pBack;

	pBack = destroyer;
	pBack->pNext = nullptr;

	curSize--;
}


template<class T>
bool LinkedList<T>::search(const T& elem)const {


	node* it = pFront;

	while (it != nullptr) {

		if (it->data == elem)
			return true;

		it = it->pNext;

	}

	return false;
}

template<class T>
void LinkedList<T>::print()const {

	node* it = pFront;

	while (it != nullptr) {

		//it->data.Print();
		std::cout << it->data << ' ';

		it = it->pNext;
	}

	std::cout << '\n';
}




template<class T>
bool LinkedList<T>::isEmpty()const {

	return curSize == 0;


}

template<class T>
int LinkedList<T>::getSize()const {

	return curSize;
}
