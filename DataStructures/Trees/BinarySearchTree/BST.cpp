#include<stdexcept> //std::exception
#include<stdio.h> //printf

//needed for printing tree nice looking in the console
#include<queue> //std::queue
#include<utility> //std::pair

#include "BST.h"


BST::BST() : root(nullptr) {

	//...
}

BST::~BST() {

	rec_destroyTree(root);
}



BST::BST(const BST& other) {

	copyFrom(other);
}

BST& BST::operator=(const BST& other) {

	if (this != &other) {

		rec_destroyTree(root);
		root = nullptr;

		copyFrom(other);
	}

	return *this;

}

void BST::rec_destroyTree(node* root) {

	if (root != nullptr) {

		rec_destroyTree(root->pLeft);
		rec_destroyTree(root->pRight);

		delete root;

	}

}

void BST::copyFrom(const BST& other) {

	rec_copyTree(root, other.root);
}

void BST::rec_copyTree(node*& newTree, node* toCopy) {

	if (toCopy == nullptr) {
		newTree = nullptr;
		return;
	}

	newTree = new node(toCopy->key, toCopy->data);

	rec_copyTree(newTree->pLeft, toCopy->pLeft);
	rec_copyTree(newTree->pRight, toCopy->pRight);


}

void BST::rec_insert(node*& root, const key_type& newKey, const data_type& newData) {

	if (root == nullptr) {

		root = new node(newKey, newData);
		return;
	}

	//already exists
	if (newKey == root->key)
		throw std::logic_error("insertion fail : elem with this key already exists!\n");
	
	if (newKey > root->key) {

		rec_insert(root->pRight, newKey, newData);
		return;
	}

	if (newKey < root->key) {

		rec_insert(root->pLeft, newKey, newData);
		return;
	}

}


data_type BST::rec_search(node* root,const key_type& key)const {

	//can't find it...
	if (root == nullptr)
		throw std::logic_error("no element with such key!");

	if (key == root->key)
		return root->data;

	if (key > root->key)
		return rec_search(root->pRight, key);
	
	if (key < root->key)
		return rec_search(root->pLeft, key);

}


//node*& because we have pointer redirections
void BST::rec_remove(node*& root,const key_type& key) {

	//search phase

	//there isn't elem with key "key"
	if (root == nullptr)
		throw std::logic_error("no element with such key!");

	//search right sub-tree
	if (key > root->key) {
		rec_remove(root->pRight, key);
		return;
	}

	//search left sub-tree
	if (key < root->key) {
		rec_remove(root->pLeft, key);
		return;
	}

	//remove phase

	//simple leaf
	if (!root->pLeft && !root->pRight) {

		delete root;
		root = nullptr;
		return;
	}


	//have two children
	if (root->pLeft != nullptr && root->pRight != nullptr) {

		//finding the max elem in the left sub-tree
		//and copy it's properties
		node * tmp = root->pLeft;

		while (tmp->pRight != nullptr)
			tmp = tmp->pRight;
		
		root->data = tmp->data;
		root->key = tmp->key;

		//removing the switched elem
		//which is a leaf or node with one child
		//and the removal will be a trivial operation
		rec_remove(root->pLeft,root->key);
	}
	else {  //the root have only one child
		
		node* destroyer = root;
		//have only left child
		if (root->pLeft)
			root = root->pLeft;
		else //have only right child
			root = root->pRight;
		
		delete destroyer; //release wanted node

	}

}

//using left - root - right tree iteration
void BST::rec_printSortedKeys(node* root) const{

	//root != nullptr
	if (root) {

		rec_printSortedKeys(root->pLeft);
		printf("{ key: %d , data : %d }\n",root->key,root->data);
		rec_printSortedKeys(root->pRight);

	}

}

unsigned int BST::rec_getHeight(node* root) const{

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

//the interface realizations are just callers to the recursive helpers  


void BST::insert(const key_type& newKey,const data_type& newData) {

	rec_insert(root, newKey,newData);

}

//searches for a specific key, if there is
//such key, returns a copy of its data
//else throws logic_error exception
data_type BST::search(const key_type& key) const{

	return rec_search(root, key);
}

unsigned int BST::getHeight() const{

	return rec_getHeight(root);
}


void BST::remove(const key_type& key) {

	rec_remove(root,key);

}

void BST::printSortedKeys() const{

	printf("\niterating the tree left - root - right looks like : \n\n");
	rec_printSortedKeys(root);
}


void BST::printTree() const{

	printf("\nthe tree looks something like this :\n\n");

	unsigned int height = rec_getHeight(root);


	//the 'drawing' has some constrains...
	//	if (height > 6 && other_constrains) {

	//	printf("the tree can't be drawn!\n");
	//		return;

	//}

	unsigned int curLevel = 0;
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
