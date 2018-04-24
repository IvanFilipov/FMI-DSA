
template<class T>
void DynamicArray<T>::copyFrom(const DynamicArray<T>& rhs)
{
	T* buffer = new T[rhs.m_capacity];
	m_capacity = rhs.m_capacity;
	m_size = rhs.m_size;

	for (size_t i = 0; i < m_size; i++)
		buffer[i] = rhs.m_data[i];

	delete[] m_data;
	m_data = buffer;
}

template<class T>
void DynamicArray<T>::clear()
{
	delete[] m_data;
	m_data = NULL;
	m_size = 0;
	m_capacity = 0;
}

template<class T>
DynamicArray<T>::DynamicArray()
	:m_size(0), m_capacity(0), m_data(NULL)
{}

template<class T>
DynamicArray<T>::DynamicArray(size_t capacity)
	: m_size(0), m_capacity(capacity), m_data(NULL)
{
	m_data = new T[m_capacity];
}

template<class T>
DynamicArray<T>::DynamicArray(const DynamicArray& rhs)
	: m_data(NULL)
{
	copyFrom(rhs);
}

template<class T>
DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray& rhs)
{
	if (this != &rhs)
		copyFrom(rhs);

	return *this;
}

template<class T>
DynamicArray<T>::~DynamicArray()
{
	clear();
}

/// Return current size
template<class T>
size_t DynamicArray<T>::size() const
{
	return m_size;
}

/// Return size of allocated storage capacity
template<class T>
size_t DynamicArray<T>::capacity() const
{
	return m_capacity;
}

/// Change size
template<class T>
void DynamicArray<T>::resize(size_t newCapacity)
{
	m_capacity = newCapacity;
	m_size = (newCapacity < m_size) ? newCapacity : m_size;

	T * buffer = new T[m_capacity];
	for (size_t i = 0; i < m_size; i++)
		buffer[i] = m_data[i];

	delete[] m_data;
	m_data = buffer;
}

/// Test whether vector is empty
template<class T>
bool DynamicArray<T>::empty() const
{
	return m_size == 0;
}

/// Element access at index position
template<class T>
T& DynamicArray<T>::operator[](int index)
{
	if (index < 0 || index >= m_size)
	{
		throw std::out_of_range("Invalid index");
	}

	return m_data[index];
}
template<class T>
const T& DynamicArray<T>::operator[](int index) const
{
	if (index < 0 || index >= m_size)
	{
		throw std::out_of_range("Invalid index");
	}

	return m_data[index];
}

/// Access first element
template<class T>
T& DynamicArray<T>::front()
{
	if (empty())
		throw std::out_of_range("No have elements!");

	return m_data[0];
}
template<class T>
const T& DynamicArray<T>::front() const
{
	if (empty())
		throw std::out_of_range("No have elements!");

	return m_data[0];
}

/// Access last element
template<class T>
T& DynamicArray<T>::back()
{
	if (empty())
		throw std::out_of_range("No have elements!");

	return m_data[m_size - 1];
}
template<class T>
const T& DynamicArray<T>::back() const
{
	if (empty())
		throw std::out_of_range("No have elements!");

	return m_data[m_size - 1];
}

/// Add element at the end
template<class T>
void DynamicArray<T>::push_back(T element)
{
	if (!m_capacity)
		resize(2);

	if (m_size == m_capacity)
		resize(m_capacity * 2);

	m_data[m_size++] = element;
}

/// Delete last element
template<class T>
void DynamicArray<T>::pop_back()
{
	if (!empty())
		--m_size;
}

template<class T>
void swap(T& lhs, T& rhs)
{
	if (lhs != rhs)
	{
		T temp = lhs;
		lhs = rhs;
		rhs = temp;
	}
}