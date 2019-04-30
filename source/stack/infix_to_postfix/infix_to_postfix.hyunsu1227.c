#define _CRT_SECURE_NO_WARNINGS
#define MAX_STACK_SIZE 101
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

typedef enum {
	lparen, rparen, plus, minus, divide, times, mod, eos, operand
} precedence;
char operator[] = { '(',')','+','-','/','*','%' };

precedence stack[MAX_STACK_SIZE];
int top = -1;

void infix_to_postfix(char infix[], char postfix[]);
void push(precedence token);
void stack_full();
precedence pop();
void stack_empty();
char precedence_to_char(precedence token);
precedence get_token(char a);

void main()
{
	FILE *f;
	char infix[101] = " ", postfix[101] = " ";

	if ((f = fopen("input.txt", "r+")) == NULL) {
		fprintf(stderr, "there is no file");
		exit(1);
	}
	fgets(infix, 100, f);

	fclose(f);

	infix_to_postfix(infix, postfix);
	printf("%s\n", postfix);
}
void infix_to_postfix(char infix[], char postfix[])
{
	precedence token, pop_token = eos;
	int len = strlen(infix), j = 0;
	int isp[] = { 0,19,12,12,13,13,13,0 };
	int icp[] = { 20,19,12,12,13,13,13,0 };

	push(eos);
	for (int i = 0; i < len; i++) {
		token = get_token(infix[i]);
		if (token == operand) {
			postfix[j] = infix[i];
			j++;
		}
		else {
			if (token == rparen) {
				while (pop_token != lparen) {
					pop_token = pop();
					if (pop_token != lparen) {
						postfix[j] = precedence_to_char(pop_token);
						j++;
					}
				}
			}
			else {
				while (1) {
					if (isp[stack[top]] < icp[token]) {
						push(token);
						break;
					}
					else {
						pop_token = pop();
						postfix[j] = precedence_to_char(pop_token);
						j++;
					}
				}
			}
		}
	}
	while (top > -1) {
		pop_token = pop();
		postfix[j] = precedence_to_char(pop_token);
		j++;
	}

}
precedence get_token(char a)
{
	switch (a)
	{
	case '(': return lparen;
	case ')': return rparen;
	case '+': return plus;
	case '-': return minus;
	case '*': return times;
	case '/': return divide;
	case '%': return mod;
	case ' ': return eos;
	default: return operand;
	}
}
char precedence_to_char(precedence token)
{
	switch (token)
	{
	case lparen: return '(';
	case rparen: return ')';
	case plus: return '+';
	case minus: return '-';
	case times: return '*';
	case divide: return '/';
	case mod: return '%';
	case eos: return ' ';
	default: return ' ';
	}
}

void push(precedence token)
{
	top++;
	if (top >= MAX_STACK_SIZE) {
		stack_full();
	}
	stack[top] = token;
}
void stack_full()
{
	fprintf(stderr, "stack is full");
	exit(1);
}
precedence pop()
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