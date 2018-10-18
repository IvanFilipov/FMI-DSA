#pragma once

template<class T>
class DynamicArray
{
private:
	T * m_data;
	size_t m_size;
	size_t m_capacity;

public:
	class Iterator
	{
	private:
		T * pElement;
		size_t pos;
	public:
		Iterator(T * element, size_t pos)
			:pElement(element), pos(pos)
		{}
		Iterator(const Iterator& other)
			:pElement(other.pElement), pos(other.pos)
		{}

	public:
		const T& operator*() const
		{
			return *pElement;
		}
		T& operator*()
		{
			return *pElement;
		}

		const T* operator->() const
		{
			return pElement;
		}
		T* operator->()
		{
			return pElement;
		}

		Iterator&  operator++()
		{
			++pElement;
			++pos;
			return *this;
		}

		Iterator operator++(int)
		{
			Iterator res(*this);
			++(*this);
			return res;
		}

		bool operator==(const Iterator& other) const
		{
			return pElement == other.pElement;
		}

		bool operator!=(const Iterator& other) const
		{
			return !(*this == other);
		}
	};
public:
	DynamicArray();
	DynamicArray(size_t capacity);
	DynamicArray(const DynamicArray<T>& rhs);
	DynamicArray<T>& operator=(const DynamicArray<T>& rhs);
	~DynamicArray();


public:
	/// Return current size
	size_t size() const;

	/// Return size of allocated storage capacity
	size_t capacity() const;

	/// Change size
	void resize(size_t n);

	/// Test whether vector is empty
	bool empty() const;

	/// Element access at index position
	T& operator[](int index);
	const T& operator[](int index) const;

	/// Access first element
	T& front();
	const T& front() const;

	/// Access last element
	T& back();
	const T& back() const;

	/// Add element at the end
	void push_back(T element);

	/// Delete last element
	void pop_back();

	/// Return iterator to beginning
	Iterator begin()
	{
		return Iterator(&m_data[0], 0);
	}

	/// Return iterator to end
	Iterator end()
	{
		return Iterator(&m_data[m_size], m_size);
	}

	/// Clean content
	void clear();

private:
	void copyFrom(const DynamicArray& rhs);
};

/// Swap two elements
template<class T>
void swap(T& lhs, T& rhs);

#include"DynamicArray.hpp"