#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct adjNode {
	int data;
	struct adjNode* next;
}adjNode;

typedef struct Graph {
	int vertexNum, edgeNum;
	adjNode **adjList;
	char type;
}Graph;

void addAdjNodeTo(adjNode** head, int data) {
	adjNode* temp = (adjNode*)malloc(sizeof(adjNode));
	temp->data = data; temp->next = NULL;
	if (*head == NULL) {
		*head = temp;
	}
	else {
		while ((*head)->next != NULL) *head = (*head)->next;
		(*head)->next = temp;
 	}
}

getDirectedGraphEdge(Graph* g, FILE* fp) {
	int vertex1, vertex2;
	for (int i = 0; i < g->edgeNum; i++) {
		fscanf(fp, "%d %d", &vertex1, &vertex2);
		addAdjNodeTo(&(g->adjList[vertex1]), vertex2);
	}
}

getUndirectedGraphEdge(Graph* g, FILE* fp) {
	int vertex1, vertex2;
	for (int i = 0; i < g->edgeNum; i++) {
		fscanf(fp, "%d %d", &vertex1, &vertex2);
		addAdjNodeTo(&(g->adjList[vertex1]), vertex2);
		if(vertex1 != vertex2)
		addAdjNodeTo(&(g->adjList[vertex2]), vertex1);
	}
}

Graph* createGraph() {
	Graph* g = (Graph*)malloc(sizeof(Graph));
	FILE* fp = fopen("input.txt", "r");
	fscanf(fp, "%c %d %d", &(g->type), &(g->vertexNum), &(g->edgeNum));
	g->adjList = (adjNode**)malloc(sizeof(adjNode*)*(g->vertexNum));
	for (int i = 0; i < g->vertexNum; i++) {
		g->adjList[i] = (adjNode*)malloc(sizeof(adjNode));
		g->adjList[i] = NULL;
	}

	if		(g->type == 'd') getDirectedGraphEdge(g, fp);
	else if (g->type == 'u') getUndirectedGraphEdge(g, fp);
	else				     exit(1);
	
	fclose(fp);

	return g;
}


void printGraph(Graph* g) {
	adjNode* head = NULL;
	for (int i = 0; i < g->vertexNum; i++) {
		head = g->adjList[i];
		while (head != NULL) {
			printf("(%d -> %d) ", i, head->data);
			head = head->next;
		}
		printf("\n");
	}
}

int main(void) {
	Graph* g = createGraph();
	printGraph(g);
	return 0;
}