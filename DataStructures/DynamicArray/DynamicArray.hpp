#include<iostream>

template<class T>
class DynamicArray{

private :

	T* pData;
	size_t curSize;
	size_t capacity;

	bool isSorted;

public:

	//THE BIG FOUR
	DynamicArray() ;
	~DynamicArray();
	DynamicArray(const DynamicArray<T>&);
	DynamicArray<T>& operator=(const DynamicArray<T>&);

	//helpers
private:

	void copyFrom(const DynamicArray<T>&);
    void free();
	void resize(size_t);

	int binarySearch(const T&, size_t, size_t )const;
	int linearSearch(const T&)const;


public:

	//add a new elem in the end
	void pushBack(const T&);
	//removes the last elem
	void popBack(); //both with amortized O(1) complexity,
					//because memory reallocations


	//new elem on random position
	void insertAt(size_t,const T&);

	//removes an elem on random position
	void removeAt(size_t);

	const T& getAt(size_t)const;
	void setAt(size_t,const T&);
	const T& operator[](size_t)const;
	T& operator[](size_t);

	size_t getSize()const;
	size_t getCapacity()const;

	//searches for an element and returns it's index if founded  , -1 else
	int search(const T&)const;

	//sorts the vector using the simple insertion sort algorithm
	void sort();

	//simple print functions
	void printInfo()const;

	void printElems()const;

};

template<class T>
DynamicArray<T>::DynamicArray():pData(nullptr), curSize(0), capacity(0){

	/*...*/
}



template<class T>
DynamicArray<T>::~DynamicArray(){

	free();
}

template<class T>
void DynamicArray<T>::free(){
	
	delete[] pData;

	pData = nullptr;
	curSize = 0;
	capacity = 0;

}

template<class T>
void DynamicArray<T>::copyFrom(const DynamicArray<T> &other){

	free();

	pData = new T[other.capacity];

	//memcpy(data, other.data, sizeof(T)*other.CurSize);
	//will not do the trick, because it will make a shallow copy of
	//our objects

	for (int i = 0; i < other.curSize; i++)
		pData[i] = other.pData[i];
	

	curSize = other.curSize;
	capacity = other.capacity;
	isSorted = other.isSorted;
}
template<class T>
DynamicArray<T>::DynamicArray(const DynamicArray<T> &other):pData(nullptr),curSize(0),capacity(0){

	copyFrom(other);

}

template<class T>
DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray<T> &other){

	if (this != &other){

		free();
		copyFrom(other);

	}

	return *this;

}

template<class T>
void DynamicArray<T>::resize(size_t newCap){


	T *temp = pData;

	pData = new T[newCap];

	for (int i = 0; i < curSize; i++)
		pData[i] = temp[i];
	

	capacity = newCap;

	delete[] temp;
}

template<class T>
void DynamicArray<T>::pushBack(const T& elem){

	if (curSize >= capacity){

		size_t newCap = (capacity == 0 ? 2 : capacity * 2);
		resize(newCap);
	}

	pData[curSize++] = elem;

	if (curSize == 1) {

		isSorted = true;
		return;
	}

	if(pData[curSize - 2] > pData[curSize - 1])
		isSorted = false;

}

template<class T>
void DynamicArray<T>::popBack() {

	if (curSize)
		curSize--;
	else
		throw std::length_error("already empty!");

	if (curSize * 2 <= capacity) {

		size_t newCap = ((curSize == 0) ? 0 : capacity / 2);
		resize(newCap);
	}

}

template<class T>
void DynamicArray<T>::insertAt(size_t pos, const T& newElem){
	
	bool sortedBefore = isSorted;

	pushBack(newElem); //will take care of the memory 

	if (pos >= curSize) //the element should be the last one
		return;

	if (sortedBefore)
		isSorted = true; //maybe our elem will go to its sorted position

	//now we should 'roll' our element back to the wanted position 
	for (size_t i = curSize - 1; i > pos; i--) {

		if (pData[i] > pData[i - 1])
			isSorted = false;

		std::swap(pData[i], pData[i - 1]);
	}

}



template<class T>
void DynamicArray<T>::setAt(size_t pos, const T& elem){


	if (pos >= curSize)
		throw std::out_of_range("Can't set a non-existent element");

	pData[pos] = elem;

}

template<class T>
void DynamicArray<T>::removeAt(size_t pos) {

	if (pos >= curSize || curSize == 1) { //just removes the last elem
		popBack();
		return;
	}

	if (!isSorted) { //faster version O(1), but can be unexpected
		
		std::swap(pData[curSize - 1], pData[pos]);	 //from the class' client
		popBack();
		return;
	}

	//else ..
	for(size_t i = pos; i < curSize-1 ;i++)
		std::swap(pData[i], pData[i+1]);

	popBack();

}
template<class T>
const T& DynamicArray<T>::getAt(size_t pos)const{

	if (pos  >= curSize)
		throw std::out_of_range("out of range!!!");

	return pData[pos];
}

template<class T>
const T& DynamicArray<T>::operator[](size_t pos)const{

	getAt(pos);
}

template<class T>
T& DynamicArray<T>::operator[](size_t pos){

	if (pos >= curSize)
		throw std::out_of_range("out of range!!!");

	return pData[pos];
}

template<class T>
size_t DynamicArray<T>::getSize()const{

	return curSize;
}

template<class T>
size_t DynamicArray<T>::getCapacity()const{

	return capacity;
}


template<class T>
void DynamicArray<T>::sort() {

	if (isSorted)
		return;

	//complexity O(n^2)
	for (int i = 1; i < curSize; i++)
		for (int j = i; j >= 1; j--)
			if (pData[j] < pData[j - 1])
				std::swap(pData[j], pData[j - 1]);

	isSorted = true;

}

template<class T>
int DynamicArray<T>::search(const T& e) const{

	if (isSorted) {

		std::cout << "using binary search ";
		return binarySearch(e, 0, curSize); // O(logn)
	}
	else {

		std::cout << "using linear search ";
		return linearSearch(e);            //O(n)
	}
}

template<class T>
int DynamicArray<T>::binarySearch(const T& e, size_t L, size_t R)const {

	//there is no such element
	if (L == R && pData[L] != e)
		return -1;

	size_t med = (L + R) / 2;

	if (pData[med] == e)
		return med;

	if (pData[med] > e)
		return binarySearch(e, L, med - 1);

	if(pData[med] < e)
		return binarySearch(e, med + 1, R);


}

template<class T>
int DynamicArray<T>::linearSearch(const T& e) const{

	for (int i = 0; i < curSize; i++)
		if (pData[i] == e)
			return i;

	return -1;

}

template<class T>
void DynamicArray<T>::printInfo()const{

	std::cout << "obj at: Ox" << this
		<< " buffer starts at: Ox" << pData
		<< " length:" << curSize
		<< " capacity:" << capacity << std::endl;

}


//T should have operator<< redefined
template<class T>
void DynamicArray<T>::printElems()const {

	for (int i = 0; i < curSize; i++)
		std::cout << pData[i] << "/";

	std::cout << std::endl;

}