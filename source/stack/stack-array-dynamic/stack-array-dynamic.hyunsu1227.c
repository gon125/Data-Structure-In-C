#define _CRT_SECURE_NO_WARNINGS
#define MAX_STACK_SIZE 1001
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
	int data;
}element;

element *stack;
int top = -1;
int capacity = 1;

void push(element item);
void stack_full();
element pop();
void stack_empty();

void main()
{
	stack = (element*)malloc(sizeof(element)*capacity);
}
void push(element item)
{
	top++;
	if (top >= capacity) {
		stack_full();
	}
	stack[top] = item;
}
void stack_full()
{
	capacity *= 2;
	stack = realloc(stack, sizeof(sizeof(element)*capacity));
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