#include<iostream>

#include<vector>
#include<string>

//just including the name for the 'std' namespace
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
	std::vector<Node> sons;

	Node(){

		value = 0;
		degree = 0;
		visited = false;

	}

};

//returns true if two trees are isomorphic 
bool areIsomorphic(Node& rootT1, Node& rootT2){

	//can't be isomorphic
	if (rootT1.degree != rootT2.degree)
		return false;

	//we have only leaves for sons
	if (rootT1.degree == rootT1.sons.size() &&
		rootT2.degree == rootT2.sons.size())
		return true;

	//we have leaves
     if (rootT1.degree == 0) // T1.degree == T2.degree
		return true;

    //have we found a subtree in T2 isomorphic to a son of T1
	bool found = false;

	//searching for a son from T2 , which is isomorphic to a son form T1 
	for (int i = 0; i < rootT1.sons.size(); i++){

		found = false;

		for (int j = 0; j < rootT2.sons.size()&&!found; j++){

			if (rootT1.sons[i].degree == rootT2.sons[j].degree 
				&& rootT2.sons[j].visited == false){

				rootT2.sons[j].visited = true;

				//checks the subtrees for isomorphism
				if (areIsomorphic(rootT1.sons[i], rootT2.sons[j]))
					found = true;
				else
					rootT2.sons[j].visited = false;

			}
		}

		if (!found)
			return false;

	}


	//every subtree of T1 has an isomorphic tree in T2
	//then found == true
	return found;


}



//reading the input relaying on that 
//the given expression is a valid one
void readTree(Node& root,string& input,int& strpos){


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
				root.sons.push_back(newSon);

				int backIndex = root.sons.size() - 1;

				//reading the children of the current son
				readTree(root.sons[backIndex], input, strpos);

				//adding the new degree to the root's one
				root.degree += root.sons[backIndex].degree + 1;
			}

			strpos++;
		}

	}

}




int main(){

	int readPos = 0;

	string input;

	//roots of the two trees
	Node T1 ,T2;

	std::cin >> input;

	readTree(T1, input,readPos);

	input.clear();

	std::cin >> input;

	readPos = 0;
	readTree(T2, input, readPos);


	if (areIsomorphic(T1, T2))
		std::cout << "YES! \n";
	else
		std::cout << "NO! \n";


	return 0;

}