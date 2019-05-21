#define _CRT_SECURE_NO_WARNINGS
#define TRUE			(1)
#define FALSE			(0)
#define MAX_VERTICES	(100)
#include <stdio.h>
#include <stdlib.h>

short int visited[MAX_VERTICES];

typedef struct adjNode* nodePointer;

typedef struct adjNode {
	int vertex;
	nodePointer link;
}adjNode;

adjNode* graph[MAX_VERTICES];

typedef struct queue *queuePointer;
typedef struct queue {
	int vertex;
	queuePointer link;
}queue;
queuePointer front, rear;

void addq(int v) {
	queuePointer temp = (queuePointer)malloc(sizeof(queue));
	temp->link = NULL; temp->vertex = v;

	if (rear == NULL) {
		front = rear = temp;
	}
	else {
		rear->link = temp; rear = temp;
	}
}

int deleteq() {
	int tempV; queuePointer temp;
	if (front == NULL) exit(1);
	temp = front; tempV = front->vertex; front = front->link;
	if (front == NULL) rear = NULL;
	free(temp);
	return tempV;
}

void bfs(int v) {
	nodePointer w;
	front = rear = NULL;
	printf("%5d", v);
	visited[v] = TRUE;
	addq(v);
	while (front) {
		v = deleteq();
		for (w = graph[v]; w; w = w->link)
			if (!visited[w->vertex]) {
				printf("%5d", w->vertex);
				addq(w->vertex);
				visited[w->vertex] = TRUE;
			}
	}
}

insertNode(adjNode** head, int data) {
	adjNode* temp = (adjNode*)malloc(sizeof(adjNode));
	adjNode* last = *head;
	/*
	temp->vertex = data; temp->link = *head;
	*head = temp;
	*/
	temp->vertex = data; temp->link = NULL;

	if (*head == NULL) { *head = temp; }
	else {
		while (last->link != NULL) { last = last->link; }
		last->link = temp;
	}
}

int main(void) {
	FILE* fp = fopen("input.txt", "r");
	char type; int vertexNum, edgeNum, vertex1, vertex2;
	int v = 0;
	fscanf(fp, "%c %d %d", &(type), &(vertexNum), &(edgeNum));
	for (int i = 0; i < edgeNum; i++) {
		fscanf(fp, "%d %d", &vertex1, &vertex2);
		insertNode(&graph[vertex1], vertex2);
		if (type == 'u' && vertex1 != vertex2) insertNode(&graph[vertex2], vertex1);
	}
	bfs(v);
	return 0;
}