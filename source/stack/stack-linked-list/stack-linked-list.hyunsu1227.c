#define _CRT_SECURE_NO_WARNINGS
#define MAX_STACK_SIZE 1001
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
	int data;
}element;

typedef struct node *stackPointer;
struct node {
	element data;
	stackPointer link;
};

stackPointer stack = NULL;

void push(element item);
element pop();
void stack_empty();

void main()
{
	
}
void push(element item)
{
	stackPointer temp = (stackPointer)malloc(sizeof(*temp));

	temp->data = item;
	temp->link = stack;
	
	stack = temp;
}
element pop()
{
	if (stack == NULL) {
		stack_empty();
	}
	element item = stack->data;
	stackPointer temp = stack;

	stack = stack->link;
	free(temp);

	return item;
}
void stack_empty()
{
	fprintf(stderr, "stack is empty");
	exit(1);
}