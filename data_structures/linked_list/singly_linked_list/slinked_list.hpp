#include <stdexcept>
#include <iosfwd> //forward declarations of ostreams

template<typename T>
class slinked_list {

private:
	//an inner representation of each "box" 
	struct node {

		T data;
		node* next_ptr;
		
		//a simple constructor
		node(const T& ndata, node* pnext = nullptr) :
			data(ndata), next_ptr(pnext) { /**/ }
	};

private :
	
	node* front_ptr;
	node* back_ptr;
	size_t cur_size;

public:

	//very basic forward iterator
	class iterator {
		//only the container will have access to the private data of iterators
		friend class slinked_list<T>;
		
	private:

		node* node_ptr;

	public:
		//lets make our iterator more STL friendly 
		//see more at : https://en.cppreference.com/w/cpp/iterator/iterator_traits
		typedef iterator                  self_type;
		typedef T                         value_type;
		typedef T&                        reference;
		typedef T*                        pointer;
		typedef std::forward_iterator_tag iterator_category;
		typedef ptrdiff_t                 difference_type;
		//basic constructor
		iterator(node* n) : node_ptr(n) { }
		
	public:
		
		//access operators
		reference operator*() { return node_ptr->data; }
		
		pointer operator->() { return &node_ptr->data; }
		
		//compare operators
		bool operator==(const iterator& rhs) const { return node_ptr == rhs.node_ptr; }
		bool operator!=(const iterator& rhs) const { return !(rhs == *this); }
		
		//increment operators
		self_type& operator++() {
			
			node_ptr = node_ptr->next_ptr;
			return *this;
		}

		self_type operator++(int) {

			self_type res(*this);
			++(*this);
			return res;
		}
	};

	//the big four
public:

	slinked_list();
	slinked_list(const slinked_list& rhs);
	slinked_list& operator=(const slinked_list& rhs);
	~slinked_list();


	//help functions
private:

	void copy_from(const slinked_list& rhs);
	
	//interface
public:
	//frees the memory allocated for all list boxes
	void clear();
	
	//adds element at the end O(1)
	void push_back(const T& el);
	//adds element at the beginning O(1)
	void push_front(const T& el); 
	//lookup for the last element O(1)
	const T& back() const;
	T& back();
	//lookup for the first element O(1)
	const T& front() const;
	T& front();
	//remove the last element O(n)
	void pop_back();
	//remove the first element O(1)
	void pop_front();
	//simply outputs the contain of the list
	void print_elems(std::ostream& os) const;
	//searches the list for a given element, if found
	//returns an iterator to it, else iterator : end(), O(n)
	iterator find(const T& el) const;

	bool is_empty() const;
	size_t get_size() const;
	
	//inserts a new element, after the element pointed by it O(1)
	iterator insert_after(const iterator& it, const T& el);
	//removes the element after the element pointed by it O(1)
	iterator remove_after(const iterator& it);
	
	iterator begin() {

		return iterator(front_ptr);
	}

	iterator end() {

		return iterator(nullptr);
	}
};


template<typename T>
slinked_list<T>::slinked_list() : 
	front_ptr(nullptr), back_ptr(nullptr), cur_size(0) {

	//...
}

template<typename T>
slinked_list<T>::slinked_list(const slinked_list<T>& rhs) : 
	front_ptr(nullptr), back_ptr(nullptr), cur_size(0) {

	copy_from(rhs);
}

template<typename T>
slinked_list<T>& slinked_list<T>::operator=(const slinked_list<T>& rhs) {

	if (this != &rhs) {

		clear();
		copy_from(rhs);
	}

	return *this;
}

template<typename T>
slinked_list<T>::~slinked_list() {

	clear();
}


template<typename T>
void slinked_list<T>::copy_from(const slinked_list<T>& rhs) {

	if (rhs.is_empty())
		return;

	try {
		//copy head
		front_ptr = new node(rhs.front_ptr->data);

		node* to_copy_it = rhs.front_ptr;
		node* copier_it = front_ptr;

		while (to_copy_it->next_ptr != nullptr) {

			to_copy_it = to_copy_it->next_ptr;

			copier_it->next_ptr = new node(to_copy_it->data);
			copier_it = copier_it->next_ptr;
		}

		back_ptr = copier_it;

	} catch (std::bad_alloc&) {

		clear();
		throw;
	}

	cur_size = rhs.cur_size;
}

template<typename T>
void slinked_list<T>::clear() {

	node* destroyer;

	while (front_ptr != nullptr) {

		destroyer = front_ptr;
		front_ptr = front_ptr->next_ptr;

		delete destroyer;
	}

	front_ptr = nullptr;
	back_ptr = nullptr;
	cur_size = 0;
}


template<typename T>
void slinked_list<T>::push_front(const T& el) {

	if (is_empty()) {

		front_ptr = new node(el);
		back_ptr = front_ptr;
		cur_size++;
		return;
	}

	node* new_elem = new node(el);

	new_elem->next_ptr = front_ptr;
	front_ptr = new_elem;

	cur_size++;
}

template<typename T>
void slinked_list<T>::push_back(const T& el) {

	if (is_empty()) {
			
		push_front(el);
		return;
	}

	back_ptr->next_ptr = new node(el);
	back_ptr = back_ptr->next_ptr;

	cur_size++;
}

template<typename T>
T& slinked_list<T>::front() {

	return const_cast<T&>(
		static_cast<const slinked_list&>(*this).front()
	);
}

template<typename T>
const T& slinked_list<T>::front() const {

	if (is_empty())
		throw std::logic_error("the list is empty!");

	return front_ptr->data;
}

template<typename T>
T& slinked_list<T>::back() {

	return const_cast<T&>(
		static_cast<const slinked_list&>(*this).back()
	);
}

template<typename T>
const T& slinked_list<T>::back() const {

	if (is_empty())
		throw std::logic_error("the list is empty!");
		
	return back_ptr->data;
}

template<typename T>
void slinked_list<T>::pop_front() {

	if (is_empty())
		throw std::logic_error("the list is empty!");

	node* destroyer = front_ptr;
	front_ptr = front_ptr->next_ptr;
	delete destroyer;

	cur_size--;
}


template<typename T>
void slinked_list<T>::pop_back() {

	if (is_empty())
		throw std::logic_error("the list is empty!");
	
	if(cur_size == 1) {
		
		delete front_ptr;
		
		front_ptr = nullptr;
		back_ptr = nullptr;
		cur_size = 0;
	}
	
	node* destroyer = front_ptr;

	while (destroyer->next_ptr != back_ptr) {

		destroyer = destroyer->next_ptr;
	}

	delete back_ptr;

	back_ptr = destroyer;
	back_ptr->next_ptr = nullptr;

	cur_size--;
}


template<typename T>
typename slinked_list<T>::iterator slinked_list<T>::find(const T& elem) const {

	node* it = front_ptr;

	while (it != nullptr) {

		if (it->data == elem)
			return iterator(it);

		it = it->next_ptr;
	}
	//same as end()
	return iterator(nullptr);
}

template<typename T>
typename slinked_list<T>::iterator slinked_list<T>::
	insert_after(const slinked_list<T>::iterator& it, const T& el) {
	
	//insert after the last element
	if(it == end() || it.node_ptr == back_ptr) {
			
		push_back(el);
		return iterator(back_ptr);
	}
	
	node* new_node = new node(el);

	new_node->next_ptr = it.node_ptr->next_ptr;

	it.node_ptr->next_ptr = new_node;

	return new_node;
}
template<typename T>
typename slinked_list<T>::iterator slinked_list<T>::
	remove_after(const slinked_list<T>::iterator& it) {
	
	if(is_empty())
		throw std::logic_error("empty queue!");
		
	if (it.node_ptr->next_ptr == nullptr)
			return end();
	
	if(it.node_ptr->next_ptr == back_ptr) {
			
		delete back_ptr;
		back_ptr = it.node_ptr;
		back_ptr = nullptr;
		return iterator(back_ptr);
	}
	
	node* to_delete = it.node_ptr->next_ptr;
	
	//we will have node_ptr->next_ptr->next_ptr, because, the ptr->next_ptr is not the last element
	it.node_ptr->next_ptr = it.node_ptr->next_ptr->next_ptr;

	delete to_delete;

	return it.node_ptr->next_ptr;
}

template<typename T>
void slinked_list<T>::print_elems(std::ostream& os) const {

	os << "content : ";
	
	if(cur_size == 0) {
		
		os << "{}" << std::endl;	
		return;
	}
	
	if(cur_size == 1) {
		
		os << '{' << front_ptr->data << '}' << std::endl;
		return;
	}
	
	os << "{ ";
	node* it = front_ptr;

	while (it->next_ptr != nullptr) {

		//it->data.Print();
		os << it->data << ", ";
		it = it->next_ptr;
	}
		
	os << it->data << " }" << std::endl;
}

template<typename T>
inline
bool slinked_list<T>::is_empty() const {

	return cur_size == 0;
}


template<typename T>
inline
size_t slinked_list<T>::get_size() const {

	return cur_size;
}
