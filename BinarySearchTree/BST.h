#pragma once

typedef int KeyType;
typedef int DataType;

class BST {


private:

	struct Node {

		KeyType Key;
		DataType Data;

		Node* pLeft;
		Node* pRight;

		Node(KeyType k = 0, DataType d = 0) : Key(k), Data(d),
			pLeft(nullptr), pRight(nullptr) {

			//...
		}

	};

	Node* root;

public:

	BST();
	~BST();
	BST(BST&);
	BST& operator=(const BST&);

private:

	//helpers
	void DestroyTree(Node*);
	void CopyTree(Node*&,Node*);

	void CopyFrom(const BST&);

	void Insert(Node*&, const KeyType&, const DataType&);

	DataType* Search(Node*,const KeyType&);

	void Remove(Node*&,Node*&,const KeyType&);

	

public:

	//Interface
	void Insert(const KeyType&, const DataType& );
	void Remove(const KeyType&);
	DataType* Search(const KeyType&);


};
