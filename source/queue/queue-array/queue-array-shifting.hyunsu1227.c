#define _CRT_SECURE_NO_WARNINGS
#define MAX_QUEUE_SIZE 5
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
	int data;
}element;

element queue[MAX_QUEUE_SIZE];
int front = -1, rear = -1;

void addq(element item);
void array_shifting();
void queue_full();
element deleteq();
void queue_empty();

void main()
{

}
void addq(element item)
{
	rear += 1;
	if (rear >= MAX_QUEUE_SIZE && front == -1) {
		queue_full();
	}
	if (rear >= MAX_QUEUE_SIZE) {
		array_shifting();
	}
	queue[rear] = item;
}
void array_shifting()
{
	int j = 0;
	printf("array shifting\n");
	for (int i = front + 1; i <= rear; i++) {
		queue[j] = queue[i];
		j++;
	}
	front = -1, rear = j;
}
void queue_full()
{
	fprintf(stderr, "queue is full");
	exit(1);
}
element deleteq()
{
	if (front == rear) {
		queue_empty();
	}
	front += 1;
	return queue[front];
}
void queue_empty()
{
	fprintf(stderr, "queue is empty");
	exit(1);
}