#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef int tElement;
typedef struct tNode {
	tElement data;
	struct tNode *leftChild, *rightChild;
}tNode;

typedef tNode* qElement;

typedef struct qNode {
	qElement data;
	struct qNode* next;
}qNode;

typedef struct tree{
	tNode* root;
	int nodeNum;
}tree;

typedef struct queue {
	qNode *front, *rear;
}queue;

qElement dequeue(queue* q) {
	qNode* deleted = q->front;
	qElement deletedItem;
	if (q->front == NULL) {
		exit(1);
	}
	deletedItem = deleted->data;
	q->front = q->front->next; free(deleted);
	if (q->front == NULL) q->rear = NULL;
	return deletedItem;
}

void enqueue(queue* q, qElement item) {
	qNode* newNode = (qNode*)malloc(sizeof(qNode));
	newNode->data = item;
	newNode->next = NULL;
	if (q->rear == NULL) {
		q->front = newNode; q->rear = newNode;
	}
	else {
		q->rear->next = newNode;
		q->rear = newNode;
	}
}

queue* createQ() {
	queue* q = (queue*)malloc(sizeof(queue));
	q->front = NULL; q->rear = NULL;
	return q;
}

tNode* createTNode(tElement item) {
	tNode* newNode = (tNode*)malloc(sizeof(tNode));
	newNode->data = item;
	newNode->leftChild = NULL; newNode->rightChild = NULL;
	return newNode;
}

tNode* searchLevelOrder(tree* t) {
	tNode* cur = t->root; queue* q = createQ();
	enqueue(q, cur);
	while (q->front != NULL) {
		cur = dequeue(q);
		if (cur->leftChild == NULL) {
			return cur;
		}
		else {
			enqueue(q, cur->leftChild);
			if (cur->rightChild == NULL) {
				return cur;
			}
			else {
				enqueue(q, cur->rightChild);
			}
		}
	}
	exit(1);
	return NULL;
}

void insert(tree* t, tElement item) {
	tNode* parentOfLast;
	//int i = ++(t->nodeNum);
	if (t->root == NULL) {
		t->root = createTNode(item);
	}
	else {
		parentOfLast = searchLevelOrder(t);

		if (parentOfLast->leftChild == NULL) {
			parentOfLast->leftChild = createTNode(item);
		}
		else if (parentOfLast->rightChild == NULL) {
			parentOfLast->rightChild = createTNode(item);
		}

	}
}

void insertInput(tree* t) {
	FILE* fp = fopen("input.txt", "r");
	tElement temp = -1;
	while (!feof(fp)) {
		fscanf(fp, "%d", &temp);
		insert(t, temp);
	}
	fclose(fp);
}

tree* createT() {
	tree* t = (tree*)malloc(sizeof(tree));
	t->root = NULL; t->nodeNum = 0;
	insertInput(t);
	return t;
}

inOrder(tNode* current) {
	if (current != NULL) {
		inOrder(current->leftChild);
		printf("%3d", current->data);
		inOrder(current->rightChild);
	}
}

preOrder(tNode* current) {
	if (current != NULL) {
		printf("%3d", current->data);
		preOrder(current->leftChild);
		preOrder(current->rightChild);
	}
}

postOrder(tNode* current) {
	if (current != NULL) {
		postOrder(current->leftChild);
		postOrder(current->rightChild);
		printf("%3d", current->data);
	}
}

levelOrder(tNode* current) {
	queue* q = createQ();
	enqueue(q, current);
	while (q->front != NULL) {
		current = dequeue(q);
		if (current->leftChild != NULL) {
			enqueue(q, current->leftChild);
		}
		if (current->rightChild != NULL) {
			enqueue(q, current->rightChild);
		}
		printf("%3d", current->data);
	}
}

int main(void) {
	//create complete binary tree with elements in "input.txt"
	tree* t = createT();
	
	inOrder(t->root);
	printf("\n");
	preOrder(t->root);
	printf("\n");
	postOrder(t->root);
	printf("\n");
	levelOrder(t->root);
	printf("\n");
	return 0;
}