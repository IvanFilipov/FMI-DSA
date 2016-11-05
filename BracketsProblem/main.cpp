#include<iostream>
#include"LinkedStack.h"

int main(){

	char buff[1024];

	std::cin.getline(buff, 1024);

	LinkedStack<char> openedBrackeds;

	bool correct = true;
	
	int i = 0;

	while (buff[i]!='\0'&&correct){

		if (buff[i] == '{' || buff[i] == '(' ||
			buff[i] == '[' || buff[i] == '<'){

			openedBrackeds.push(buff[i]);
			i++;
			continue;
		}

		switch (buff[i]){

		case '}': if (openedBrackeds.peek() != '{'){
			correct = false;
		}
				  else openedBrackeds.pop();
				  break;
		case ')': if (openedBrackeds.peek() != '('){
			correct = false;
		}
				  else openedBrackeds.pop();
				  break;

		case '>': if (openedBrackeds.peek() != '<'){
			correct = false;
		}
				  else openedBrackeds.pop();
				  break;

		case ']': if (openedBrackeds.peek() != '['){
			correct = false;
		}
				  else openedBrackeds.pop();
				  break;
		}

		i++;
	}

	if (correct&&openedBrackeds.isEmpty()){

		std::cout << "correct input\n";
	}
	else{
		std::cout << "input is not correct\n";
	}


	return 0;
}