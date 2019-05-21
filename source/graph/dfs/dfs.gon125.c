#define _CRT_SECURE_NO_WARNINGS
#define TRUE			(1)
#define FALSE			(0)
#define MAX_VERTICES	(100)
#include <stdio.h>
#include <stdlib.h>

short int visited[MAX_VERTICES];

typedef struct adjNode {
	int vertex;
	struct adjNode* link;
}adjNode;

adjNode* graph[MAX_VERTICES];

void dfs(int v) {
	adjNode* w;
	visited[v] = TRUE;
	printf("%5d", v);
	for (w = graph[v]; w; w = w->link)
		if (!visited[w->vertex])
			dfs(w->vertex);
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
	dfs(v);
	return 0;
}