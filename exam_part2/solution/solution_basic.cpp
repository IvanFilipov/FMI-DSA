#include<fstream> //std::ifstream used to read the file's contain

#include<iostream> //std::cout, std::cerr

//represents a node in binary tree
struct Node {

	unsigned int val;

	Node* pLeft;
	Node* pRight;

	Node(unsigned int v = 0, Node* l = nullptr, Node* r = nullptr) :
		val(v), pLeft(l), pRight(r) {}

	//C++ 11 way to forbid compile-generated copy constructor and operator=
	Node& operator=(const Node&) = delete;
	Node(const Node&) = delete;

};

//needed to free the allocated memory
void destroyTree(Node* root) {

	if (root == nullptr)
		return;

	destroyTree(root->pLeft);
	destroyTree(root->pRight);

	delete root;

}

// 1 reading

//reading a tree from a file recursively 
Node* readTreeFromFile(std::ifstream& ifs) {

	char c = ifs.get();

	if (!ifs.good())
		return nullptr;

	char nextChar;

	if (c == '(') {

		//empty tree case
		nextChar = ifs.get();

		if (nextChar == ')')
			return nullptr;
		else
			ifs.unget(); //returning it back

		Node* tree = new Node;

		//reading the value in the root
		ifs >> tree->val;

		//reading left subtree
		tree->pLeft = readTreeFromFile(ifs);

		if (tree->pLeft)
			ifs.get(); // reading the ')' bracket on the way back 

		//reading right subtree
		tree->pRight = readTreeFromFile(ifs);

		if (tree->pLeft)
			ifs.get(); // reading the ')' bracket on the way back 

		return tree;

	}
	else
		return nullptr; //some kind of error in the input...

}

// 2 bloom tree
void bloomTree(Node* root) {

	if (root == nullptr)
		return;

	//is leaf
	if (root->pLeft == nullptr &&
		root->pRight == nullptr) {

		root->pLeft = new Node(root->val);
		root->pRight = new Node(root->val);

		return;
	}

	//else try it's children
	bloomTree(root->pLeft);
	bloomTree(root->pRight);

}

//3 accumulate tree
unsigned int accumTree(const Node* root) {

	if (root == nullptr)
		return 0;

	return root->val + accumTree(root->pLeft)
					 + accumTree(root->pRight);

}

void testTreeFromFile(const char* filePath) {

	if (filePath == nullptr)
		return;

	std::cout << "reading the tree from " << filePath
		<< std::endl;

	std::ifstream ifs(filePath);

	if (!ifs.is_open()) {

		std::cerr << "can't open the file!" << std::endl;
		return;
	}

	Node* root = readTreeFromFile(ifs);

	if (root == nullptr) {

		std::cerr << "empty tree or invalid file!" << std::endl;
		return;

	}

	unsigned int firstSum = accumTree(root);
	std::cout << "accumulate : " << firstSum
		<< std::endl;

	bloomTree(root);
	std::cout << "after blooming the tree" << std::endl;

	unsigned int secondSum = accumTree(root);
	std::cout << "accumulate : " << secondSum
		<< std::endl;

	std::cout << "accum(T\') - accum(T) = " 
		<< secondSum - firstSum
		<< std::endl;

	//cleaning everything
	destroyTree(root);
	root = nullptr;
	ifs.close();

	std::cout << std::endl;
}


int main() {

	testTreeFromFile("tree.txt");

	testTreeFromFile("tree1.txt");
	
	return 0;
}