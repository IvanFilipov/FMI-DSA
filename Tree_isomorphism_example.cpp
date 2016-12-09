#include<iostream>
#include"DynamicArray.h"
#include<string>

using std::string;


//simple structure to represent every tree node
struct Node{

	//the useless value
	int value;

	//number of sub trees
	int degree;

	//used for the algorithm
    bool visited;

	//contains all sons of the current node
	DynamicArray<Node> sons;

	Node(){

		value = 0;
		degree = 0;
		visited = false;

	}

};


//returns true if two trees are isomorphic 
bool AreIsomorphic(Node& T1, Node& T2){

	//can't be isomorphic
	if (T1.degree != T2.degree)
		return false;

	//we have only leaves for sons
	if (T1.degree == T1.sons.GetSize() && T2.degree == T2.sons.GetSize())
		return true;

	//we have leaves
     if (T1.degree == 0) // T1.degree == T2.degree
		return true;

    //have we found a subtree in T2 isomorphic to a son of T1
	bool found = false;


	//searching for a son from T2 , which is isomorphic to a son form T1 
	for (int i = 0; i < T1.sons.GetSize(); i++){

		found = false;

		for (int j = 0; j < T2.sons.GetSize()&&!found; j++){

			if (T1.sons[i].degree == T2.sons[j].degree && T2.sons[j].visited == false){

				T2.sons[j].visited = true;

				//checks the subtrees for isomorphism
				if (AreIsomorphic(T1.sons[i], T2.sons[j]))
					found = true;
				else
					T2.sons[j].visited = false;

			}
		}

		if (!found)
			return false;

	}


	//every subtree of T1 has an isomorphic tree in T2
	if (found)
		return true;


}



//reading the input
void ReadTree(Node& root,string& input,int& strpos){


	while (input[strpos] != '\0'){

		//reading the root
		if (input[strpos] == '('){

			strpos++;

			//reading a number
			char num[12];
			int numpos = 0;

			while(isdigit(input[strpos])){
             	num[numpos++] = input[strpos++];
			}

			num[numpos] = '\0';

			root.value = atoi(num);
		}


		//end of current tree
		if (input[strpos] == ')'){
			strpos++;
			return;
		}

		//reading sons of current root
		if (input[strpos] == '{'){

			strpos++;

			if (input[strpos] == '}')
				root.degree = 0;


			while (input[strpos] != '}'){

				Node newSon;

				//adding the new son
				root.sons.PushBack(newSon);

				int backIndex = root.sons.GetSize() - 1;

				//reading the children of the current son
				ReadTree(root.sons[backIndex], input, strpos);

				//adding the new degree to the root's one
				root.degree += root.sons[backIndex].degree + 1;
			}

			strpos++;
		}

	}

}




int main(int argc,char* argv[]){

	if (argc < 3){
		std::cout << "not enough arguments!\n";
		return -1;
	}


	int Readpos = 0;

	string input(argv[1]);

	//roots of the two trees
	Node T1 ,T2;

	//std::cin >> input;

	ReadTree(T1, input,Readpos);

	//input.clear();

	//std::cin >> input;

	input = argv[2];

	Readpos = 0;
	ReadTree(T2, input, Readpos);


	if (AreIsomorphic(T1, T2))
		std::cout << "YES! \n";
	else
		std::cout << "NO! \n";


	return 0;

}