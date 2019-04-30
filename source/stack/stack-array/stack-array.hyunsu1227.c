#define _CRT_SECURE_NO_WARNINGS
#define MAX_STACK_SIZE 1001
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
	int data;
}element;

element stack[MAX_STACK_SIZE];
int top = -1;

void push(element item);
void stack_full();
element pop();
void stack_empty();

void main()
{
	
}
void push(element item)
{
	top++;
	if (top >= MAX_STACK_SIZE){
		stack_full();
	}
	stack[top] = item;
}
void stack_full()
{
	fprintf(stderr, "stack is full");
	exit(1);
}
element pop()
{
	if (top == -1) {
		stack_empty();
	}
	return stack[top--];
}
void stack_empty()
{
	fprintf(stderr, "stack is empty");
	exit(1);
}