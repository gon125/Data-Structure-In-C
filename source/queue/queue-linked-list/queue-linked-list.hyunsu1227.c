#define _CRT_SECURE_NO_WARNINGS
#define MYSTR1 "2012123456"
#define MYSTR2 "ȫ�浿"
#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node *nodePointer;
struct node {
	int a;
	nodePointer link;
};
nodePointer front, rear;

void addq(int a);
int deleteq();
void queueEmpty();
void printQueue(nodePointer front);

int main()
{	
	int op = 0;
	int cnt = 0;
	while (1) {
		printf("addq 1��, deleteq 2��, queue ��ü ��� 3��, ���� 4��\n");
		scanf("%d", &op);
		if (op == 1) {
			addq(cnt);
			cnt++;
			printQueue(front);
		}
		else if (op == 2) {
			deleteq();
			printQueue(front);
		}
		else if (op == 3) {
			printQueue(front);
		}
		else if (op == 4) {
			printf("�����մϴ�.\n");
			break;
		}

	}
	
	return 0;
}

void addq(int a) 
{
	nodePointer temp = malloc(sizeof(*temp));
	temp->a = a;
	temp->link = NULL;

	if (front == NULL) {
		front = temp;
	}
	else {
		rear->link = temp;
	}
	rear = temp;
}

int deleteq()
{
	if (front == NULL) {
		queueEmpty();
	}
	nodePointer temp = front;
	int result = front->a;
	front = front->link;

	free(temp);
	return result;
}

void queueEmpty()
{
	fprintf(stderr, "queue is empty");
	exit(EXIT_FAILURE);
}

void printQueue(nodePointer front)
{
	while (front != NULL) {
		printf("%d ", front->a);
		front = front->link;
	}
	printf("\n");
}