//the simplest implementation of static stack
//written in C, so could be compile using gcc

#include<stdio.h>


#define MAXN 10
#define INPUTN 7 

typedef int data;

data stack[MAXN];
int top;

void init() {

	top = 0;
}

int isEmpty() {

	return top == 0;
}

void push(data elem) {

	if (top == MAXN)
		fprintf(stderr, "not enough space in the stack!");
	else
		stack[top++] = elem;

}

data pop() {

	if (isEmpty()) {

		fprintf(stderr, "empty stack!");
		return 0;
	}

	return stack[--top];

}


int main() {

	int cnt = INPUTN;
	data p;
	init();

	do {
		scanf("%d", &p);
		push(p);

	} while (--cnt);

	while (!isEmpty())
		printf("%d ", pop());

	printf("\n");
	return 0;
}