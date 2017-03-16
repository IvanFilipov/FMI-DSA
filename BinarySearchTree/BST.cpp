#include "BST.h"
#include<stdexcept>


BST::BST() : root(nullptr) {

	//...
}

BST::~BST() {

	DestroyTree(root);
	root = nullptr;

}



BST::BST(BST& other) {

	CopyFrom(other);
}

BST& BST::operator=(const BST& other) {

	if (this != &other) {

		DestroyTree(root);
		root = nullptr;
		CopyFrom(other);
	}

	return *this;

}

void BST::DestroyTree(Node* root) {

	if (root != nullptr) {

		DestroyTree(root->pLeft);
		DestroyTree(root->pRight);

		delete root;

	}


}

void BST::CopyTree(Node*& newTree, Node* toCopy) {

	if (toCopy == nullptr) {
		newTree = nullptr;
		return;
	}

	newTree = new Node(toCopy->Key, toCopy->Data);

	CopyTree(newTree->pLeft, toCopy->pLeft);
	CopyTree(newTree->pRight, toCopy->pRight);


}

void BST::CopyFrom(const BST& other) {
	
	CopyTree(root, other.root);
}


void BST::Insert(const KeyType& newKey,const DataType& newData) {

	Insert(root, newKey,newData);

}

void BST::Insert(Node*& root, const KeyType& newKey, const DataType& newData) {

	

	if (root == nullptr) {

		root = new Node(newKey, newData);
		return;
	}

	if (newKey == root->Key)
		throw std::logic_error("already exists");


	if (newKey > root->Key) {

		Insert(root->pRight, newKey, newData);
		return;
	}

	if (newKey < root->Key) {

		Insert(root->pLeft, newKey, newData);
		return;
	}

}

DataType* BST::Search(const KeyType& key) {

	return Search(root, key);
}

DataType* BST::Search(Node* root,const KeyType& key) {

	if (root == nullptr)
		return nullptr;

	if (key == root->Key)
		return &(root->Data);

	if (key > root->Key)
		return Search(root->pRight, key);
	
	if (key < root->Key)
		return Search(root->pLeft, key);

}




void BST::Remove(const KeyType& key) {
	Node* null = nullptr;
	Remove(root,null, key);

}

void BST::Remove(Node*& root,Node*& last,const KeyType& key) {

	//search phase

	//there isn't elem with key "key"
	if (root == nullptr)
		return; //can be exception or std::err , or std::cout

	if (key > root->Key) {
		Remove(root->pRight,root, key);
		return;
	}

	if (key < root->Key) {
		Remove(root->pLeft,root, key);
		return;
	}

	//remove phase

	//have two children
	if (root->pLeft != nullptr && root->pRight != nullptr) {

		//finding the max elem in the left sub-tree
		Node * tmp = root->pLeft;

		while (tmp->pRight != nullptr) {
			tmp = tmp->pRight;
		}
		
		root->Data = tmp->Data;
		root->Key = tmp->Key;

		//removing the switched elem
		Remove(root->pLeft,root, root->Key);


	}
	else {  //one child or none
		
		if (root->pLeft) {
			if (root->pLeft->pLeft||root->pLeft->pRight)
			{
				Node* temp = root;
				last->pLeft = root->pLeft;

				delete[] temp;
				temp = nullptr;

				return;
			}

			root->Data = root->pLeft->Data;
			root->Key = root->pLeft->Key;
			root = root->pLeft;

		}

		if (root->pRight) {
			if (root->pRight->pLeft || root->pRight->pRight)
			{
				Node* temp = root;
				last->pRight = root->pRight;

				delete[] temp;
				temp = nullptr;

				return;
			}

			root->Data = root->pRight->Data;
			root->Key = root->pRight->Key;
			root = root->pLeft;

		}

		delete root;
		root = nullptr;

	}

}