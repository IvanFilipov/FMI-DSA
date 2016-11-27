#include<iostream>
#include"LinkedStack.h"

double Calc(char c, double left, double right){

	switch (c){

	case '+': return  left + right;
	case '-': return  left - right;
	case '*': return left * right;
	case '/': return left / right;
	}


}



int main(){

	LinkedStack<double> a;

	char buffer [1024];

	std::cin.getline(buffer, 1024);

	int len = strlen(buffer);

	int i = 0;
	double left, right;

	while (i<len){

		if (buffer[i] >= '0'&&buffer[i] <= '9'){

			a.push(double(buffer[i] - '0')); //ascii -> double
		}
		
		if (buffer[i] == '+' || buffer[i] == '-' || buffer[i] == '*' || buffer[i] == '/'){
		
			if (a.getSize() < 2){
				return -1;
			}

			right = a.peek(); a.pop();
			left = a.peek(); a.pop();
			a.push(Calc(buffer[i], left, right));
		}

		i++;
	}

	double answer = a.peek();
	a.pop();

	if (a.isEmpty()){
		std::cout << "answer is : " << answer;
	}
	else{
		return -1;
	}


	

	return 0;
}


