#define _CRT_SECURE_NO_WARNINGS
#define MAX_TERMS 1001
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

typedef struct node *treePointer;
struct node {
	char data;
	treePointer leftChild, rightChild;
};
typedef struct queue *linkPointer;
struct queue {
	treePointer item;
	linkPointer link;
};

void inorder(treePointer ptr);
treePointer input(char a);
void preorder(treePointer ptr);
void postorder(treePointer ptr);
void addq(treePointer item);
treePointer deleteq();
void queueEmpty();
void levelorder(treePointer ptr);

treePointer root = NULL, root2 = NULL;
linkPointer front = NULL, rear = NULL;

void main()
{
	root = (treePointer)malloc(sizeof(*root));
	root->data = 'A';
	root->leftChild = input('B');
	root->rightChild = input('C');
	root->leftChild->leftChild = input('D');
	root->leftChild->rightChild = input('E');
	root->rightChild->leftChild = input('F');
	root->rightChild->rightChild = input('G');
	root->leftChild->leftChild->leftChild = input('H');
	root->leftChild->leftChild->rightChild = input('I');

	root2 = (treePointer)malloc(sizeof(*root));
	root2->data = '+';
	root2->leftChild = input('*');
	root2->rightChild = input('E');
	root2->leftChild->leftChild = input('*');
	root2->leftChild->rightChild = input('D');
	root2->leftChild->leftChild->leftChild = input('/');
	root2->leftChild->leftChild->rightChild = input('C');
	root2->leftChild->leftChild->leftChild->leftChild = input('A');
	root2->leftChild->leftChild->leftChild->rightChild = input('B');

	printf("Preorder: ");
	preorder(root);
	printf("\n");

	printf("Inorder: ");
	inorder(root);
	printf("\n");

	printf("Postorder: ");
	postorder(root);
	printf("\n");

	printf("Levelorder: ");
	levelorder(root);
	printf("\n\n");

	printf("Preorder: ");
	preorder(root2);
	printf("\n");

	printf("Inorder: ");
	inorder(root2);
	printf("\n");

	printf("Postorder: ");
	postorder(root2);
	printf("\n");

	printf("Levelorder: ");
	levelorder(root2);
	printf("\n\n");
}

treePointer input(char a)
{
	treePointer temp = (treePointer)malloc(sizeof(*temp));
	temp->data = a;
	temp->leftChild = NULL;
	temp->rightChild = NULL;
	return temp;
}

void inorder(treePointer ptr)
{
	if (ptr)
	{
		inorder(ptr->leftChild);
		printf("%c", ptr->data);
		inorder(ptr->rightChild);
	}
}
void preorder(treePointer ptr)
{
	if (ptr)
	{
		printf("%c", ptr->data);
		preorder(ptr->leftChild);
		preorder(ptr->rightChild);
	}
}
void postorder(treePointer ptr)
{
	if (ptr)
	{
		postorder(ptr->leftChild);
		postorder(ptr->rightChild);
		printf("%c", ptr->data);
	}
}
void levelorder(treePointer ptr)
{
	treePointer item = NULL;

	addq(ptr);
	while (front != NULL)
	{
		item = deleteq();
		printf("%c", item->data);
		if (item->leftChild != NULL) {
			addq(item->leftChild);
		}
		if (item->rightChild != NULL) {
			addq(item->rightChild);
		}
	 } 
}
void addq(treePointer item)
{
	linkPointer temp = (linkPointer)malloc(sizeof(*temp));
	temp->item = item;
	temp->link = NULL;

	if (!front) {
		front = temp;
	}
	else {
		rear->link = temp;
	}
	rear = temp;
}
treePointer deleteq()
{
	linkPointer temp = front;
	if (!front) {
		queueEmpty();
	}
	treePointer item = front->item;

	front = front->link;
	free(temp);

	return item;
}
void queueEmpty()
{
	fprintf(stderr, "queue is empty");
	exit(1);
}