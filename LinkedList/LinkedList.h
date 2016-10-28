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
	int CurSize;


public:
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

	};

	//the big four
public:

	LinkedList();
	LinkedList(const LinkedList&);
	LinkedList& operator=(const LinkedList&);
	~LinkedList();


	//help functions
private:

	void CopyFrom(const LinkedList&);
	void Clean();

	//interface
public:

	void PushBack(const T&);
	void PushFront(const T&);

	const T& Back()const;
	const T& Front()const;

	void PopBack();
	void PopFront();


	void Print()const;
	bool Search(const T&)const;

	bool isEmpty()const;
	int getSize()const;

	Iterator Beg() {

		return Iterator(pFront);

	}

	Iterator End() {

		return Iterator(pBack->pNext);
	}

};


template<class T>
LinkedList<T>::LinkedList() :pFront(nullptr), pBack(nullptr), CurSize(0) {

	//...
}

template<class T>
LinkedList<T>::LinkedList(const LinkedList<T>& other) :pFront(nullptr), pBack(nullptr), CurSize(0) {

	CopyFrom(other);
}

template<class T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& other) {

	if (this != &other) {

		Clean();
		CopyFrom(other);

	}

	return *this;
}

template<class T>
LinkedList<T>::~LinkedList() {

	Clean();
}


template<class T>
void LinkedList<T>::CopyFrom(const LinkedList<T>& other) {

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

		Clean();
		throw;
	}

	CurSize = other.CurSize;

}

template<class T>
void LinkedList<T>::Clean() {

	node * destroyer;

	while (pFront != nullptr) {

		destroyer = pFront;
		pFront = pFront->pNext;

		delete destroyer;


	}

	pFront = nullptr;
	pBack = nullptr;
	CurSize = 0;
}


template<class T>
void LinkedList<T>::PushFront(const T& elem) {

	if (isEmpty()) {

		pFront = new node(elem);
		pBack = pFront;
		CurSize++;
		return;

	}

	node* NewElem = new node(elem);

	NewElem->pNext = pFront;
	pFront = NewElem;

	CurSize++;


}

template<class T>
void LinkedList<T>::PushBack(const T& elem) {

	if (isEmpty()) {

		pFront = new node(elem);
		pBack = pFront;
		CurSize++;
		return;

	}

	pBack->pNext = new node(elem);
	pBack = pBack->pNext;

	CurSize++;


}

template<class T>
const T& LinkedList<T>::Front()const {

	if (isEmpty())
		throw std::exception("the list is empty!");

	return pFront->data;

}

template<class T>
const T& LinkedList<T>::Back()const {

	if (isEmpty())
		throw std::exception("the list is empty!");

	return pBack->data;

}

template<class T>
void LinkedList<T>::PopFront() {

	if (isEmpty())
		throw std::exception("the list is empty!");

	node * destroyer = pFront;

	pFront = pFront->pNext;

	delete destroyer;

	CurSize--;

}


template<class T>
void LinkedList<T>::PopBack() {

	if (isEmpty())
		throw std::exception("the list is empty!");

	node * destroyer = pFront;

	while (destroyer->pNext != pBack) {

		destroyer = destroyer->pNext;

	}

	delete pBack;

	pBack = destroyer;
	pBack->pNext = nullptr;

	CurSize--;
}


template<class T>
bool LinkedList<T>::Search(const T& elem)const {


	node* it = pFront;

	while (it != nullptr) {

		if (it->data == elem)
			return true;

		it = it->pNext;

	}

	return false;
}



template<class T>
void LinkedList<T>::Print()const {

	node* it = pFront;

	while (it != nullptr) {

		//it->data.Print();
		std::cout << it->data;

		it = it->pNext;
	}

	std::cout << '\n';
}




template<class T>
bool LinkedList<T>::isEmpty()const {

	return CurSize == 0;


}

template<class T>
int LinkedList<T>::getSize()const {

	return CurSize;
}