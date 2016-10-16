#include<iostream>

template<class T>
class DynamicArray{

private :

	T *data;
	size_t CurSize;
	size_t Capacity;

	
private:

    //helpers
    void CopyFrom(const DynamicArray<T>&);
    void Free();
	void Resize(size_t NewSize);
	
	
public:

	//THE BIG FOUR
	DynamicArray() ;
	~DynamicArray();
	DynamicArray(const DynamicArray<T>&);
	DynamicArray<T>& operator=(const DynamicArray<T>&);


	void PushBack(const T&);
	const T& GetAt(size_t)const;
	void SetAt(size_t,const T&);
	const T& operator[](size_t)const;
	T& operator[](size_t);

	size_t GetSize()const;
	size_t GetCapacity()const;

	void PrintInfo()const;
	
	//TODO search( linear , binary ) , sort 
	
	
};

template<class T>
DynamicArray<T>::DynamicArray():data(nullptr), CurSize(0), Capacity(0){

	/*...*/
}



template<class T>
DynamicArray<T>::~DynamicArray(){
	Free();
}

template<class T>
void DynamicArray<T>::Free(){
	
	delete[] data;

	data = nullptr;
	CurSize = 0;
	Capacity = 0;

}

template<class T>
void DynamicArray<T>::CopyFrom(const DynamicArray<T> &other){

	Free();

	data = new T[other.CurSize];

	//memcpy(data, other.data, sizeof(T)*other.CurSize);

	for (int i = 0; i < other.CurSize; i++){

		data[i] = other.data[i];
	}

	CurSize = other.CurSize;
	Capacity = other.Capacity;

}
template<class T>
DynamicArray<T>::DynamicArray(const DynamicArray<T> &other):data(nullptr),CurSize(0),Capacity(0){

	CopyFrom(other);

}

template<class T>
DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray<T> &other){

	if (this != &other){

		CopyFrom(other);

	}

	return *this;

}

template<class T>
void DynamicArray<T>::Resize(size_t NewCap){


	T *temp = data;

	data = new T[NewCap];

	for (int i = 0; i < CurSize; i++){

		data[i] = temp[i];
	}

	Capacity = NewCap;

	delete[] temp;
}

template<class T>
void DynamicArray<T>::PushBack(const T& elem){

	if (CurSize >= Capacity){

		size_t NewCap = (Capacity == 0 ? 2 : Capacity * 2);
		Resize(NewCap);
	}

	data[CurSize++] = elem;

}

template<class T>
void DynamicArray<T>::SetAt(size_t pos, const T& elem){


	if (pos >= CurSize){

		throw std::out_of_range;

	}

	data[pos] = elem;

}

template<class T>
const T& DynamicArray<T>::GetAt(size_t pos)const{

	if (pos  >= CurSize){

		throw std::out_of_range("out of range!!!");

	}

	return data[pos];
}

template<class T>
const T& DynamicArray<T>::operator[](size_t pos)const{


	GetAt(pos);
}

template<class T>
T& DynamicArray<T>::operator[](size_t pos){

	if (pos >= CurSize){
		throw std::out_of_range("out of range!!!");
	}

	return data[pos];
}

template<class T>
size_t DynamicArray<T>::GetSize()const{

	return CurSize;
}

template<class T>
size_t DynamicArray<T>::GetCapacity()const{

	return Capacity;
}


template<class T>
void DynamicArray<T>::PrintInfo()const{

	std::cout << "obj at: Ox" << this
		<< " buffer starts at: Ox" << data
		<< " length:" << CurSize
		<< " capacity:" << Capacity << std::endl;

}