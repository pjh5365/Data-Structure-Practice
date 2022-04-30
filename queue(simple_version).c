#include <stdio.h>
#define MAX 10

typedef struct queue{
	int data[MAX];
	int front;
	int rear;
}Queue;

void enqueue(Queue *q, int data) {
	q->data[q->rear++] = data;
}

int dequeue(Queue *q) {
	int remove;
	remove = q->data[q->front++];
	return remove;
}

void print_queue(Queue *q) {
	int i;
	for(i = q->front; i < q->rear; i++)
		printf("%d\n", q->data[i]);
	printf("\n");
}

int main(void){
	Queue q;
	q.front = q.rear= 0;
	
	enqueue(&q, 1);
	enqueue(&q, 2);
	enqueue(&q, 3);
	enqueue(&q, 4);
	enqueue(&q, 5);
	
	print_queue(&q);
	printf("\n\n%d", dequeue(&q));
	printf("\n%d\n\n", dequeue(&q));
	print_queue(&q);
	
	return 0;
}
