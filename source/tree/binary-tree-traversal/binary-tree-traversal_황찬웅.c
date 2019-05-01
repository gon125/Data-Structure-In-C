#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define MALLOC(p,s) if(!(p=malloc(s))){printf("insufficient memory");exit(1);}

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

treePointer createTree1() {
	treePointer temp=NULL;
	temp = createNode('A');
	temp->leftchild = createNode('B');
	temp->rightchild = createNode('C');
	temp->leftchild->leftchild = createNode('D');
	temp->leftchild->rightchild = createNode('E');
	temp->rightchild->leftchild = createNode('F');
	temp->rightchild->rightchild = createNode('G');
	temp->leftchild->leftchild->leftchild = createNode('H');
	temp->leftchild->leftchild->rightchild = createNode('I');
	return temp;
}
treePointer createTree2() {
	treePointer temp=NULL;	
	temp = createNode('+');
	temp->rightchild = createNode('E');
	temp->leftchild = createNode('*');
	temp->leftchild->rightchild = createNode('D');
	temp->leftchild->leftchild = createNode('*');
	temp->leftchild->leftchild->rightchild = createNode('C');
	temp->leftchild->leftchild->leftchild = createNode('/');
	temp->leftchild->leftchild->leftchild->rightchild = createNode('B');
	temp->leftchild->leftchild->leftchild->leftchild = createNode('A');
	return temp;
}

void inorder(treePointer ptr) {
	if (ptr) {
		inorder(ptr->leftchild);
		printf("%c", ptr->data);
		inorder(ptr->rightchild);
	}
}
void preorder(treePointer ptr) {
	if (ptr) {
		printf("%c", ptr->data); 
		preorder(ptr->leftchild);
		preorder(ptr->rightchild);
	}
}
void postorder(treePointer ptr) {
	if (ptr) {
		postorder(ptr->leftchild);
		postorder(ptr->rightchild);
		printf("%c", ptr->data);
	}
}

void printTree(treePointer root) {
	printf("  preorder  : "); preorder(root); printf("\n");
	printf("  inorder   : "); inorder(root); printf("\n");
	printf("  postorder : "); postorder(root); printf("\n\n");
}

void main() {
	treePointer root1=NULL;
	treePointer root2=NULL;

	root1 = createTree1();
	root2 = createTree2();
	
	printf(" tree1\n"); printTree(root1);
	printf(" tree2\n"); printTree(root2);	
}