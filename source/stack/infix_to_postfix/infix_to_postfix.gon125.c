#define _CRT_SECURE_NO_WARNINGS
#define MAX_INPUT_SIZE (100)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef enum precedence { lparen, rparen, plus, minus, times, divide, mod, eos, operand }precedence;
// in stack precedence
int isp[] = { 0, 19, 12, 12, 13, 13, 13, 0 };
// incoming precedence
int icp[] = { 20, 19, 12, 12, 13, 13, 13, 0 };
typedef precedence sElement;
typedef char qElement;

typedef struct sNode{
	sElement data;
	struct sNode *link;
}sNode;

typedef struct qNode{
	qElement data;
	struct qNode *link;
}qNode;

typedef struct stack{
	sNode* top;
}stack;

typedef struct queue{
	qNode *front, *rear;
}queue;

stack* createS() {
	stack* s = (stack*)malloc(sizeof(stack));
	s->top = NULL;
	return s;
}

queue* createQ() {
	queue* q = (queue*)malloc(sizeof(queue));
	q->front = NULL; q->rear = NULL;
	return q;
}

sNode* pop(stack* s) {
	sNode* poped;
	if (s->top == NULL) {
		printf("STACK EMPTY.\n");
		return NULL;
	}
	poped = s->top;
	s->top = s->top->link;
	return poped;
}

void push(stack* s, sElement item) {
	sNode* newNode = (sNode*)malloc(sizeof(sNode));
	newNode->data = item;
	newNode->link = s->top;
	s->top = newNode;
}

qNode* dequeue(queue* q) {
	qNode* deleted;
	if (q->front == NULL) {
		printf("QUEUE EMPTY.\n");
		return NULL;
	}
	deleted = q->front;
	q->front = q->front->link;
	if (q->front == NULL) q->rear = NULL;
	return deleted;
}

void enqueue(queue* q, qElement item) {
	qNode* newNode = (qNode*)malloc(sizeof(qNode));
	newNode->data = item;
	newNode->link = NULL;
	if (q->rear == NULL) { //QUEUE IS EMPTY.
		q->front = newNode; q->rear = newNode;
	}
	else { // QUEUE IS NOT EMPTY.
		q->rear->link = newNode;
		q->rear = newNode;
	}
}

char* getInput() {
	FILE* fp = fopen("input.txt", "r");
	char* input = (char*)malloc(sizeof(char)*MAX_INPUT_SIZE);
	if (fp == NULL) {
		printf("CANNOT OPEN THE FILE.");
		exit(1);
	}
	fscanf(fp, "%s", input);
	return input;
}

precedence charToPrecedence(char c) {
	switch(c) {
	case '(': return lparen;
	case ')': return rparen;
	case '+': return plus;
	case '-': return minus;
	case '*': return times;
	case '%': return mod;
	case '/': return divide;
	case '\0': return eos;
	default: return operand;
	}
}

char precedenceToChar(precedence p) {
	switch (p) {
	case plus:		return '+';
	case minus:		return '-';
	case times:		return '*';
	case mod:		return '%';
	case divide:	return '/';
	case eos:		return '\0';
	default:		return -1;
	}
}

char* infixToPostfix(char* infix) {
	char* postfix = (char*)malloc(sizeof(char)*MAX_INPUT_SIZE);
	precedence token; int i;
	int len = strlen(infix);
	stack* s = createS(); queue* q = createQ();
	// push eos to stack to keep stack not empty.
	push(s, eos);
	for (i = 0; i < len; i++) {
		token = charToPrecedence(infix[i]);
		if (token == operand) {
			enqueue(q, infix[i]);
		}
		else if (token == rparen) {
			while (s->top->data != lparen) {
				enqueue(q, precedenceToChar(pop(s)->data));
			}
			pop(s);
		}
		else {
			//Whether token's precedence is bigger than a top of  Stack or not,
			//You have to push a token to Stack anyway. So just put it at the bottom.
			//If the top of Stack is bigger than or the same as a token,
			//We will pop and enqueue it until it gets smaller.
			//Because Stack should keep elements in descending order from the top.
			while (isp[s->top->data] >= icp[token]) {
				enqueue(q, precedenceToChar(pop(s)->data));
			}
			push(s, token);
		}
	}
	// if last infix char was operand -> enqueue rest precedences of stack.
	while(s->top != NULL)
	enqueue(q, precedenceToChar(pop(s)->data));
	// index of postfix expression.
	i = 0;
	while (q->front != NULL) {
		postfix[i] = dequeue(q)->data;
		i++;
	}

	return postfix;
}

void freeAll(char* a, char* b) {
	free(a); free(b);
}

int main(void) {
	char *infix, *postfix;
	infix = getInput();
	postfix = infixToPostfix(infix);
	printf("%s", postfix);
	freeAll(infix, postfix);
	return 0;
}
