#include<iostream>
#include"DynamicStack.hpp"

//the task is to check if the brackets  
//in an arithmetic expression are perfectly matched

//{[]({})} -> true
//([)]{} -> false

int main(){

	char buff[1024];

	std::cin.getline(buff, 1024);

	DynamicStack<char> openedBrackets;

	bool correct = true;
	
	int i = 0;

	while (buff[i]!='\0' && correct){

		if (buff[i] == '{' || buff[i] == '(' ||
			buff[i] == '[' || buff[i] == '<'){

			openedBrackets.push(buff[i]);
			i++;
			continue;
		}

		switch (buff[i]){

		case '}': if (openedBrackets.peek() != '{')
						correct = false;
				  else 
					  openedBrackets.pop();
				  break;
				  
		case ')': if (openedBrackets.peek() != '(')
						correct = false;
				  else 
					  openedBrackets.pop();
				  break;

		case '>': if (openedBrackets.peek() != '<')
						correct = false;
				  else 
					  openedBrackets.pop();
				  break;

		case ']': if (openedBrackets.peek() != '[')
						correct = false;
				  else 
					  openedBrackets.pop();
				  break;
	     
		 default : correct = false ;
		 
		}

		i++;
	}

	if (correct && openedBrackets.isEmpty())
		std::cout << "correct input\n";
	else
		std::cout << "input is not correct\n";


	return 0;
}