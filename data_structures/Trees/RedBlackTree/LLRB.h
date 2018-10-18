//implementation idea and some parts of the code are taken from :
// http://www.cs.princeton.edu/~rs/talks/LLRB/RedBlack.pdf and
// http://www.teachsolaisgames.com/articles/balanced_left_leaning.html

#pragma once

//for each element we have a key and some data
typedef int key_type;
typedef int data_type;

//each not is either black or red
#define BLACK 0
#define RED 1

//left leaning red black tree
//provides O(logN) searching, inserting and removing

class LLRB {

private:
	//each node have two pointers for it's children
	struct node {

		key_type key;
		data_type data;

		node* pLeft;
		node* pRight;

		bool color; // the color of the incoming edge

		node(key_type k = 0, data_type d = 0, bool clr = RED) : key(k), data(d),
			color(clr),pLeft(nullptr), pRight(nullptr) {

			//...
		}

	};

	//the root of the tree
	node* root;

public:

	LLRB();
	~LLRB();
	LLRB(const LLRB&);
	LLRB& operator=(const LLRB&);

private:

	//helpers
	void copyFrom(const LLRB&);

	//starting with rec_ are recursive functions

	void rec_destroyTree(node*);
	void rec_copyTree(node*&,node*);

	data_type rec_search(node*,const key_type&) const;

	node* rec_insert(node*, const key_type&, const data_type&);
	node* rec_remove(node*,const key_type&);

	void rec_printSortedKeys(node*) const;

	unsigned int rec_getHeight(node*)const;

	//all we need are some balancing helpers

	//for insert 
	bool isRed(node*);

	node* leftRotate(node*);
	node* rightRotate(node*);

	void colorFlip(node*);

	//and for delete
	node* fixUp(node*);

	node* moveRedLeft(node*);
	node* moveRedRight(node*);

	node* deleteMin(node*);

public:

	//Interface
	void insert(const key_type&, const data_type& );
	void remove(const key_type&);
	data_type search(const key_type&) const;

	unsigned int getHeight()const;

	key_type getMaxKey() const;

	void printSortedKeys() const;

	void printTree()const;

};
