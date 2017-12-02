#pragma once

//for each element we have a key and some data
typedef int key_type;
typedef int data_type;

class BST {

private:
	//each node have two pointer for it's children
	struct node {

		key_type key;
		data_type data;

		node* pLeft;
		node* pRight;

		node(key_type k = 0, data_type d = 0) : key(k), data(d),
			pLeft(nullptr), pRight(nullptr) {

			//...
		}

	};

	//the root of the tree
	node* root;

public:

	BST();
	~BST();
	BST(const BST&);
	BST& operator=(const BST&);

private:

	//helpers
	void copyFrom(const BST&);

	//starting with rec_ are recursive functions
	void rec_destroyTree(node*);
	void rec_copyTree(node*&,node*);

	data_type rec_search(node*,const key_type&) const;

	void rec_insert(node*&, const key_type&, const data_type&);
	void rec_remove(node*&,const key_type&);

	void rec_printSortedKeys(node*) const;

	unsigned int rec_getHeight(node*)const;

public:

	//Interface
	void insert(const key_type&, const data_type& );
	void remove(const key_type&);
	data_type search(const key_type&) const;

	unsigned int getHeight()const;

	void printSortedKeys() const;

	void printTree()const;

};
