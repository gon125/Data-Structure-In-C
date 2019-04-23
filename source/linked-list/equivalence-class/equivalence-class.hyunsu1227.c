#define _CRT_SECURE_NO_WARNINGS
#define MAX_TERMS  101
#define MAX_STACK_SIZE 101
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef struct node *linkPointer;
struct node
{	
	int num;
	linkPointer link;
};
linkPointer top[MAX_STACK_SIZE] = { NULL };

void push(int i, int num);
int pop(int i);
void stack_empty();

void main(void)
{
	FILE *f;
	int n = 0, m = 0, pair_i = 0, pair_j = 0;
	linkPointer temp;

	if ((f = fopen("input.txt", "r+")) == NULL) {
		fprintf(stderr, "there is no file");
		exit(1);
	}
	fscanf(f, "%d %d", &n, &m);
	for (int i = 0; i < m; i++) {
		fscanf(f, "%d %d", &pair_i, &pair_j);
		push(pair_i, pair_j);
		push(pair_j, pair_i);
	}
	fclose(f);
	int *out = (int *)calloc(n, sizeof(int));

	for (int i = 0; i < n; i++) {
		if (out[i] == 0) {
			out[i] = 1;
			printf("New Class: %d", i);

			temp = top[i];
			push(n, i);
			while (top[n]) {
				while (temp) {
					if (out[temp->num] == 0) {
						printf(" %d", temp->num);
						out[temp->num] = 1;
						push(n, temp->num);
					}
					temp = temp->link;
				}
				temp = top[pop(n)];
			}
			printf("\n");
		}
	}
	free(out);
}

void push(int i, int num)
{
	linkPointer temp = (linkPointer)malloc(sizeof(*temp));
	temp->num = num;
	temp->link = top[i];
	top[i] = temp;
}

int pop(int i)
{
	linkPointer temp = top[i];
	if (temp == NULL) {
		stack_empty();
	}
	int item = temp->num;
	top[i] = top[i]->link;
	free(temp);
	return item;
}

void stack_empty()
{
	fprintf(stderr, "stack is empty");
	exit(1);
}