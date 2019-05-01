#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define MALLOC(p,s) if(!(p=malloc(s))){printf("insufficient memory");exit(1);}

FILE *F;
void FileOpen(char *fname) {
	if (((F = fopen(fname, "r+"))) == NULL) {
		if (((F = fopen(fname, "w+"))) == NULL) {
			printf("fail open");exit(1);
		}
	}
}

typedef struct node *treePointer;
typedef struct node {
	char data;
	treePointer rightchild;
	treePointer leftchild;
};

treePointer createNode(char a) {
	treePointer cur;
	MALLOC(cur, sizeof(*cur));
	cur->data = a;
	cur->leftchild = NULL;
	cur->rightchild = NULL;
	return cur;
}

typedef struct queue *queuePointer;
typedef struct queue {
	treePointer info;
	queuePointer link;
};
queuePointer front;
queuePointer roer;

void addq(treePointer a) {
	queuePointer temp;
	MALLOC(temp, sizeof(*temp));
	temp->info = a;
	temp->link = NULL;
	if (front)roer->link = temp;
	else front = temp;
	roer = temp;
}
void IsqueueEmpty() {
	if (!front) {
		printf("queue is empty");exit(1);
	}
}
treePointer deleteq() {
	IsqueueEmpty();
	treePointer item;
	queuePointer temp = front;
	front = front->link;
	item = temp->info;
	free(temp);
	return item;
}

treePointer createTree(char *a,int n) {
	int i = 1;
	treePointer temp = NULL,cur;
	temp = createNode(a[0]);
	cur = temp;
	addq(temp);
	while (i!=n) {
		temp = deleteq();
		if (temp) {
			if (!(temp->leftchild)) {
				temp->leftchild = createNode(a[i]);
				i++;
				addq(temp->leftchild);
			}
			if (!(temp->rightchild)) {
				temp->rightchild = createNode(a[i]);
				i++;
				addq(temp->rightchild);
			}
		}
	}
	while (front) {
		deleteq();
	}
	return cur;
}

void inorder(treePointer ptr) {
	if (ptr) {
		inorder(ptr->leftchild);
		if (ptr->data)printf("%c", ptr->data);
		inorder(ptr->rightchild);
	}
}
void preorder(treePointer ptr) {
	if (ptr) {
		if (ptr->data)printf("%c", ptr->data);
		preorder(ptr->leftchild);
		preorder(ptr->rightchild);
	}
}
void postorder(treePointer ptr) {
	if (ptr) {
		postorder(ptr->leftchild);
		postorder(ptr->rightchild);
		if (ptr->data)printf("%c", ptr->data);
	}
}
void levelorder(treePointer ptr) {
	if (!ptr)return;
	addq(ptr);
	while (front) {
		ptr = deleteq();
		if (ptr) {
			if(ptr->data)printf("%c", ptr->data);
			if (ptr->leftchild)addq(ptr->leftchild);
			if (ptr->rightchild)addq(ptr->rightchild);
		}
	}
}

void printTree(treePointer root) {
	printf("  preorder    : "); preorder(root); printf("\n");
	printf("  inorder     : "); inorder(root); printf("\n");
	printf("  postorder   : "); postorder(root); printf("\n");
	printf("  levelorder  : "); levelorder(root);printf("\n\n");
}

void main() {
	int i = 1, cnt = 1, j = 1;
	char tree1[100] = "ABCDEFGHI",tree[100]="+*E*D/CAB";
	char *tree2;
	MALLOC(tree2, sizeof(*tree2) * 20);
	tree2[0] = '+';
	for (i = 1;i <= 16;i++) {
		if (i == cnt) {
			tree2[i] = tree[j];j++;
			if (cnt % 2)cnt++;
			else cnt = cnt * 2 - 1;
		}
		else tree2[i] = NULL;
	}
	treePointer root1 = NULL;
	treePointer root2 = NULL;
	root1 = createTree(tree1, strlen(tree1));
	root2 = createTree(tree2, 17);
	printf("*tree1\n"); printTree(root1);
	printf("*tree2\n"); printTree(root2);
}
