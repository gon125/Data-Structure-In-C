#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define MALLOC(p,s) if(!(p=malloc(s))){printf("insufficient memory");exit(1);}

typedef struct stack *stackPointer;
typedef struct stack {
	int data;
	stackPointer link;
};
stackPointer top;

void push(int a) {
	stackPointer temp;
	MALLOC(temp, sizeof(*temp));
	temp->data = a;
	if (top)temp->link = top;
	else temp->link = NULL;
	top = temp;
}
int emptyStack() {
	if (top)return 0;
	printf("stack empty\n");return 1;
}
int pop() {
	if (emptyStack())return NULL;
	stackPointer temp;
	int item;
	temp = top;
	item = top->data;
	top = top->link;
	free(temp);
	return item;
}

void main() {
	int a;
	push(7);
	a = pop();
	if(a)printf("%d ", a);
	push(4);
	a = pop();
	if (a)printf("%d ", a);
	push(9);
	a = pop();
	if (a)printf("%d ", a);
	a = pop();
	if (a)printf("%d ", a);
}