#include<stdexcept> //std::exception
#include<stdio.h> //printf

//needed for printing tree nice looking in the console
#include<queue> //std::queue
#include<utility> //std::pair

#include "LLRB.h"


LLRB::LLRB() : root(nullptr) {

	//...
}

LLRB::~LLRB() {

	rec_destroyTree(root);
}

LLRB::LLRB(const LLRB& other) {

	copyFrom(other);
}

LLRB& LLRB::operator=(const LLRB& other) {

	if (this != &other) {

		rec_destroyTree(root);
		root = nullptr;

		copyFrom(other);
	}

	return *this;

}

void LLRB::rec_destroyTree(node* root) {

	if (root != nullptr) {

		rec_destroyTree(root->pLeft);
		rec_destroyTree(root->pRight);

		delete root;

	}

}

void LLRB::copyFrom(const LLRB& other) {

	rec_copyTree(root, other.root);
}

void LLRB::rec_copyTree(node*& newTree, node* toCopy) {

	if (toCopy == nullptr) {
		newTree = nullptr;
		return;
	}

	newTree = new node(toCopy->key, toCopy->data);

	rec_copyTree(newTree->pLeft, toCopy->pLeft);
	rec_copyTree(newTree->pRight, toCopy->pRight);

}


//as same as searching in a ordinary BST
data_type LLRB::rec_search(node* root,const key_type& key)const {

	//can't find it...
	if (root == nullptr)
		throw std::logic_error("no element with such key!");

	//here it is
	if (key == root->key)
		return root->data;

	//searching in the right sub-tree
	if (key > root->key)
		return rec_search(root->pRight, key);
	
	//searching in the left sub-tree
	if (key < root->key)
		return rec_search(root->pLeft, key);

}


//using left - root - right tree iteration
//same as in BST
void LLRB::rec_printSortedKeys(node* root) const{

	//root != nullptr
	if (root) {

		rec_printSortedKeys(root->pLeft);
		printf("{ key: %d , data : %d }\n",root->key,root->data);
		rec_printSortedKeys(root->pRight);

	}

}

//same as in BST
unsigned int LLRB::rec_getHeight(node* root) const{

	if (root) {
		//return 1 + rec_getHeight(root->pLeft) + rec_getHeight(root->pRight);

		unsigned int leftSubTreeHeight = rec_getHeight(root->pLeft);
		unsigned int rightSumTreeHeight = rec_getHeight(root->pRight);

		return 1 +
			((leftSubTreeHeight > rightSumTreeHeight) ?
				leftSubTreeHeight :
				rightSumTreeHeight);

	}
	else
		return 0;

}


//the balancing helpers

inline bool LLRB::isRed(node* pNode){

	return ((pNode != nullptr) && (pNode->color == RED)) ;
}


//left rotate :
/*      1                         2
		F                         Q
	   / \ (r)                (r)/  \
	 A-E   Q          =>        F	R - Z
		   /\                  / \
		  G-P R-Z           A-E  G-P


*/

LLRB::node* LLRB::leftRotate(node* pNode){

	node* pTemp = pNode->pRight;
	pNode->pRight = pTemp->pLeft;
	pTemp->pLeft = pNode;

	pTemp->color = pTemp->pLeft->color;
	pTemp->pLeft->color = RED;

	return pTemp;
}


//right rotate :
/*      2                         1
		F                         Q 
	   / \ (r)                (r)/  \
	 A-E   Q          <=        F	R - Z
		   /\                  / \
	    G-P   R-Z           A-E  G-P


*/
LLRB::node* LLRB::rightRotate(node* pNode){
	
	node* pTemp = pNode->pLeft;
	pNode->pLeft = pTemp->pRight;
	pTemp->pRight = pNode;

	pTemp->color = pTemp->pRight->color;
	pTemp->pRight->color = RED;

	return pTemp;

}


//color flipping
/*
            |                 |(r)
		    M       =>        M
		(r)/ \(r)            / \
		  P   Q             P    Q
*/
void LLRB::colorFlip(node * pNode){

	pNode->color = !pNode->color;

	if (pNode->pLeft)
		pNode->pLeft->color = !pNode->pLeft->color;

	if (pNode->pRight)
		pNode->pRight->color = !pNode->pRight->color;

}

LLRB::node* LLRB::rec_insert(node* root, const key_type& newKey, const data_type& newData) {

	if (root == nullptr) {

		root = new node(newKey, newData, RED); //insert red colored leaf
		return root;
	}

	//mapping with 2-3-4 trees
	//if (isRed(root->pLeft) && isRed(root->pRight)) //splitting 4-nodes on the way down
		//colorFlip(root);

	//already exists
	if (newKey == root->key)
		throw std::logic_error("insertion fail : elem with this key already exists!\n");
	
	//inserting into the right sub-tree
	if (newKey > root->key) {

		root->pRight =
			rec_insert(root->pRight, newKey, newData);		
	}
	else { //newKey < root->key

		//into the left sub-tree
		root->pLeft =
			rec_insert(root->pLeft, newKey, newData);
		
	}

	//so far everything just like in an ordinary BST 

	//after returning from the recursion we've got work
	//to do in order to balance the tree
	
	// fixes a right-leaning red node: this will assure that a 3-node is
	// the left child
	if (isRed(root->pRight))
		 root = leftRotate(root);

	// fixes two reds in a row: this will re balance a 4-node
	if (isRed(root->pLeft) && isRed(root->pLeft->pLeft))
		root = rightRotate(root);

	//a map of a 2-3 tree
	if (isRed(root->pLeft) && isRed(root->pRight)) //splitting 4-nodes on the way up
		colorFlip(root);


	// return the new root of the subtree that was just updated,
	// since rotations may have changed the value of this pointer.
	return root;

}


//the functions needed for balancing after removing a node

//fixes right - leaning reds and eliminate 4 - nodes on the way up.
LLRB::node* LLRB::fixUp(node* pNode) {

	if (isRed(pNode->pRight)) //rotate-left right-leaning reds
		pNode = leftRotate(pNode);

	if (isRed(pNode->pLeft) && isRed(pNode->pLeft->pLeft)) //rotate-right red-red pairs
		pNode = rightRotate(pNode);

	if (isRed(pNode->pLeft) && isRed(pNode->pRight)) //split 4 - nodes
		colorFlip(pNode);

	return pNode;
}


//see the example on page 61 from 
// http://www.cs.princeton.edu/~rs/talks/LLRB/RedBlack.pdf

LLRB::node* LLRB::moveRedLeft(node* pNode){
	
	colorFlip(pNode);

	if (pNode->pLeft && isRed(pNode->pLeft->pLeft)){

		pNode = rightRotate(pNode);
		colorFlip(pNode);
	}

	return pNode;
}


//see the example on page 56 from 
// http://www.cs.princeton.edu/~rs/talks/LLRB/RedBlack.pdf

LLRB::node* LLRB::moveRedRight(node* pNode){

	colorFlip(pNode);

	if (pNode->pRight && isRed(pNode->pRight->pLeft)){

		pNode->pRight = rightRotate(pNode->pRight);
		pNode = leftRotate(pNode);

		colorFlip(pNode);
	}

	return pNode;
}

LLRB::node* LLRB::deleteMin(node* pNode){
	
	//remove node on bottom level
	// due to the arrangement of an LLRB tree, the node cannot have a
	// right child
	if (!pNode->pLeft) {

		delete pNode; //!!! there is no such thing in JAVA code from the example
		return nullptr;	//because JAVA runtime has it's own garbage collector
	}

	// if these nodes are black, we need to rearrange this subtree to
	// force the left child to be red.
	if (!isRed(pNode->pLeft) && !isRed(pNode->pLeft->pLeft))
		pNode = moveRedLeft(pNode);

	// continue recursing to locate the node to delete.
	pNode->pLeft = deleteMin(pNode->pLeft);

	// fix right-leaning red nodes and eliminate 4-nodes on the way up.
	// need to avoid allowing search operations to terminate on 4-nodes,
	// or searching may not locate intended key.
	return fixUp(pNode);

}

LLRB::node* LLRB::rec_remove(node* root, const key_type& key) {

	//delete in the left sub-tree
	if (key < root->key) {

		//there is a left sub-tree
		if (root->pLeft != nullptr) {

			if (!isRed(root->pLeft) && !isRed(root->pLeft->pLeft)) //push red right if necessary
				root = moveRedLeft(root);

			root->pLeft =
				rec_remove(root->pLeft, key); //	move down(left)
		}
	}
	else {

		// If the left child is red, apply a rotation so we make
		// the right child red.
		if (isRed(root->pLeft))
			root = rightRotate(root);

		//equal at bottom aka delete a leaf
		if ((root->key == key) && (root->pRight == nullptr)) {

			delete root;
			return nullptr;
		}

		//there is a right sub-tree
		if (root->pRight != nullptr) {

			//delete in right sub-tree

			//push red right if necessary
			if ((!isRed(root->pRight)) && (!isRed(root->pRight->pLeft)))
				root = moveRedRight(root);

			if (key == root->key) { // equal not at the bottom 

				node* it = root->pRight;
				while (it->pLeft)
					it = it->pLeft;

				//copy the data and the key
				root->key = it->key;
				root->data = it->data;

				root->pRight = deleteMin(root->pRight); // delete successor
			}
			else //continue with the searching down
				root->pRight = rec_remove(root->pRight, key);

		}
	}

	//fix right-leaning red links
	//and eliminate 4 - nodes
	//on the way up
	return fixUp(root);
}


//the interface realizations are just callers to the recursive helpers  

void LLRB::insert(const key_type& newKey,const data_type& newData) {

	root = rec_insert(root, newKey,newData);

	root->color = BLACK; // the root is always black

}

void LLRB::remove(const key_type& key) {

	//will throw std::logic_error 
	//if there isn't such element
	//maybe reasonable only for debugging
	rec_search(root, key);

	if (root) { //if not empty tree
		root = rec_remove(root, key);

		if (root) 
			root->color = BLACK; //the color of the root is always black
	}

}

//searches for a specific key, if there is
//such key, returns a copy of its data
//else throws logic_error exception
data_type LLRB::search(const key_type& key) const{

	return rec_search(root, key);
}

//returns the height of the tree as known as
//the longest path from the root to a leaf
unsigned int LLRB::getHeight() const{

	return rec_getHeight(root);
}

//prints all data in nodes sorted by their keys
void LLRB::printSortedKeys() const{

	printf("\niterating the tree left - root - right looks like : \n\n");
	rec_printSortedKeys(root);
}


//a pretty tree look - like output in console
//useful to understand what is happening with the tree
//in every moment
void LLRB::printTree() const{

	printf("\nthe tree looks something like this :\n\n");

	unsigned int height = rec_getHeight(root);

	//the 'drawing' has some constrains...
	//	if (height > 6 && other_constrains) {

	//	printf("the tree can't be drawn!\n");
	//		return;

	//}

	unsigned int curLevel = 0;

	//how many spaces between the elements
	unsigned int indent = (( 1 << height + 1) / 2) - 1;

	//preforming BFS - pushing nodes form the tree and
	//empty ones in order to make the 'draw' easier

	//key - level of node
	std::queue<std::pair<node*, unsigned int>> wave;

	wave.push(std::make_pair(root, curLevel+1));

	while (curLevel <= height) {

		if (curLevel < wave.front().second) {
			curLevel = wave.front().second;
			printf("\n");

			//indent = (width / (1 << curLevel)) - curLevel;
			indent >>= 1;
			
		}

		for (int i = 0; i < indent; i++)
			printf(" ");

		if (wave.front().first != nullptr)
			printf("%3d", wave.front().first->key);
		else
			printf("  ");

		for (int i = 0; i < indent; i++)
			printf(" ");


		//if real node
		if (wave.front().first != nullptr) {
			if (wave.front().first->pLeft != nullptr)
				wave.push(std::make_pair(wave.front().first->pLeft,
					wave.front().second + 1));
			else
				wave.push(std::make_pair(nullptr, wave.front().second + 1));


			if (wave.front().first->pRight != nullptr)
				wave.push(std::make_pair(wave.front().first->pRight,
					wave.front().second + 1));
			else
				wave.push(std::make_pair(nullptr, wave.front().second + 1));

		}
		else { //fake node

			//pushing two fake children
			wave.push(std::make_pair(nullptr, wave.front().second + 1));
			wave.push(std::make_pair(nullptr, wave.front().second + 1));
		}

		wave.pop();
	}
}
