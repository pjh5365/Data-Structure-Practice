#include <stdio.h>
#define MAX 10


typedef struct stack {
	int stack[MAX];
	int top;
}Stack;

void init_stack(Stack *A) {
	A->top = -1;
}

void push(Stack *A, int data) {
	A->stack[++(A->top)] = data;
}

int pop(Stack *A) {
	return A->stack[(A->top)--];
}

int main(void) {
	
	int i, j;
	Stack A;
	init_stack(&A);
	push(&A,1);
	push(&A,2);
	push(&A,3);
	push(&A,4);
	push(&A,5);
	
	for(i = 0; i <= A.top; i++) {
		printf("[%d] ", A.stack[i]);
	}
	
	j = pop(&A);
	printf("\n\n%d\n", j);
	for(i = 0; i <= A.top; i++) {
		printf("[%d] ", A.stack[i]);
	}
	
}
