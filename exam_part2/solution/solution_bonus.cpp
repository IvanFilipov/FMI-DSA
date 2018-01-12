#include<fstream> //std::ifstream

#include<iostream> //std::cout, std::cerr

#include<math.h> //log10

//needed for prettyPrint
#include<queue> //std::queue, std::pair

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

void destroyTree(Node* root) {

	if (root == nullptr)
		return;

	destroyTree(root->pLeft);
	destroyTree(root->pRight);

	delete root;

}

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

		//reading the root's value 
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

//2 bloom tree + bonus

typedef unsigned int(*fptrBloomFunc) (unsigned int);

unsigned int id(unsigned int x) {

	return x;
}

unsigned int inc(unsigned int x) {

	return x + 1;
}

void bloomTree(Node* root, fptrBloomFunc f) {

	if (root == nullptr)
		return;

	//is leaf
	if (root->pLeft == nullptr &&
		root->pRight == nullptr) {

		root->pLeft = new Node(f(root->val));
		root->pRight = new Node(f(root->val));

		return;
	}

	//else try it's children
	bloomTree(root->pLeft, f);
	bloomTree(root->pRight, f);

}

//3 accumulate tree + bonus

typedef unsigned long long ull_int;

typedef ull_int (*fptrAcumm)(ull_int, ull_int);

ull_int sum(ull_int x,ull_int y) {

	return x + y;
}

ull_int mul(ull_int x, ull_int y) {

	return x * y;
}

ull_int accumTree(const Node* root, ull_int beg, fptrAcumm f) {

	if (root == nullptr)
		return beg;

	return f(root->val, f(accumTree(root->pLeft, beg, f),
		accumTree(root->pRight, beg, f)));
}

//pretty printing bonus

//calculates a tree's height
unsigned int getHeight(Node* root) {

	if (root == nullptr)
		return 0;

	unsigned int leftSubTreeHeight = getHeight(root->pLeft);
	unsigned int rightSumTreeHeight = getHeight(root->pRight);

	return 1 + ((leftSubTreeHeight > rightSumTreeHeight) ?
		leftSubTreeHeight :
		rightSumTreeHeight);

}

//finds the biggest element in the tree
unsigned int findMaxElem(Node* root) {

	if (root == nullptr)
		return 0;

	unsigned int res = root->val;

	unsigned int left_res = findMaxElem(root->pLeft);

	unsigned int right_res = findMaxElem(root->pRight);

	if (left_res > res)
		res = left_res;

	if (right_res > res)
		res = right_res;

	return res;
}

void prettyPrint(Node* root){

	std::cout << "\nthe tree looks something like this :\n\n";

	unsigned int height = getHeight(root);

	unsigned int curLevel = 0;

	//how many spaces between the elements : 

	//the maximum value of children in a binary tree
	//with height h is 2 ^ ( h - 1) why?
	unsigned int maxChildren = 1 << (height - 1);

	//we will have at least one space between each children
	maxChildren <<= 1; // *= 2

	//which is the longest number
	unsigned int maxElem = findMaxElem(root);

	//how many digits it has
	unsigned int maxDigits = unsigned int(log10(maxElem) + 1);

	//how many cells do we need in each line
	unsigned int indent = maxChildren * (maxDigits + 1) - 1;

	//preforming BFS - pushing nodes form the tree and
	//empty ones in order to make the 'draw' easier

	//key - level of node
	std::queue<std::pair<Node*, unsigned int>> wave;

	wave.push(std::make_pair(root, curLevel + 1));

	while (curLevel <= height) {

		if (curLevel < wave.front().second) {

			curLevel = wave.front().second;

			std::cout << std::endl;

			if (curLevel > height)
				return;

			//on each line below indent will be index / 2
			indent >>= 1;
			
		}

		for (unsigned int i = 0; i < indent; i++)
			std::cout << ' ';

		if (wave.front().first != nullptr)
			printf("%u", wave.front().first->val);
		else
			std::cout << ' '; //empty node

		for (unsigned int i = 0; i <= indent; i++)
			std::cout << ' ';

		//if real node, pushing its children into the wave
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


int main() {

	std::ifstream ifs("tree.txt");

	std::cout << "the tree from file tree.txt\n";

	if (!ifs.is_open()) {

		std::cerr << "can't open the file\n";
		return -1;
	}

	Node* root = readTreeFromFile(ifs);

	prettyPrint(root);

	ull_int firstRes = accumTree(root, 0, sum);
	std::cout << "accumulate with sum function : " << firstRes;

	bloomTree(root, id);
	std::cout << "\nafter blooming with identity function T\': \n";
	prettyPrint(root);

	ull_int secondRes = accumTree(root, 0, sum);
	std::cout << "\naccumulate with sum function : "
		<< secondRes;

	std::cout << "\naccum(T\') - accum(T) = "
		<< secondRes - firstRes;

	//cleaning everything
	destroyTree(root);
	root = nullptr;
	ifs.close();


	//testing another tree and bonus functions 
	ifs.open("tree1.txt");

	std::cout << "\n\n\nthe tree from file tree1.txt\n";

	if (!ifs.is_open()) {

		std::cerr << "can't open the file\n";
		return -1;
	}

	root = readTreeFromFile(ifs);

	prettyPrint(root);

	firstRes = accumTree(root, 1, mul);
	std::cout << "\naccumulate with multiply function : "
		<< firstRes;

	bloomTree(root, inc);
	std::cout << "\nafter blooming with +1 function T\': \n";
	prettyPrint(root);

	secondRes = accumTree(root, 1, mul);
	std::cout << "\naccumulate with multiply function : "
		<< secondRes;

	std::cout << "\naccum(T\') - accum(T) = "
		<< secondRes - firstRes;
	
	//notice that these memory releases may be unnecessary
	destroyTree(root);
	root = nullptr;
	ifs.close();

	return 0;
}