#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX 50
#define MAX_QUEUE_SIZE 50

typedef struct graph {	//�׷����� ����ü ���� 
	int vertex;
	int data[MAX_VERTEX];	//������ �����͸� ���� �迭 
	int adj_m[MAX_VERTEX][MAX_VERTEX];
}Graph;

typedef struct queue {
	int queuedata[MAX_QUEUE_SIZE];
	int front, rear;
}Queue;

int is_empty(Queue *q) {	//ť�� ����˻��Լ� 
	return (q->front == q->rear);
}

int is_full(Queue *q) {	//ť�� ��ȭ���°˻��Լ� 
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

void init_queue(Queue *q) {	//ť �ʱ�ȭ�Լ� 
	q->front = q->rear = 0;
}

void enqueue(Queue *q, char data) {	//ť�� ���Կ��� 
	if(is_full(q))
		printf("ť�� ��ȭ�����Դϴ�. \n");
		
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->queuedata[q->rear] = data;
}

char dequeue(Queue *q) {	//ť�� �������� 
	if(is_empty(q))
		printf("ť�� ��������Դϴ�. \n");
	
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->queuedata[q->front];
}

int visited[MAX_VERTEX];	//�湮�� ������ ���� �迭

void reset_visited(Graph *g) {	//�湮�� ������ ���� �迭 �ʱ�ȭ 
	int i;
	for(i = 0; i < g->vertex; i++)
		visited[i] = 0;
} 

void init_graph(Graph *g) {	//�׷����� �ʱ�ȭ �ϴ� �Լ� 
	int i, j;
	g->vertex = 0;
	
	for(i = 0; i < MAX_VERTEX; i++) {
		for(j = 0; j < MAX_VERTEX; j++)
			g->adj_m[i][j] = 0;
	}
}

void insert_vertex(Graph *g, int i) {	//�׷����� ������ �߰��ϴ� �Լ� 
		if(g->vertex +1 > MAX_VERTEX) {	
			printf("������ ���� �ʰ� \n");
			return;
		}
		g->data[g->vertex] = i;
		g->vertex++; 
}

void insert_edge(Graph *g, int start, int end) {	//������ �׷����� ���� ���� 
	if(start >= g->vertex || end >= g->vertex) {
		printf("������ ��ȣ ���� \n");
		return;
	}
	g->adj_m[start][end] = 1;
	g->adj_m[end][start] = 1;
}

void print_graph(Graph *g) {	//������� ����Լ� 
	int i, j;
	
	printf("%d \n", g->vertex);
		
	for(i = 0; i < g->vertex; i++) {
		printf("%d \t", g->data[i] + 1);	//�迭�� �ε����� �����Ͽ� +1
		for(j = 0; j < g->vertex; j++)
			printf("[%2d] ", g->adj_m[i][j]);
		
		printf("\n");
	}
} 

void DFS(Graph *g, int v) {	//������� ���̿켱Ž�� 
	int w;
	visited[v] = 1;	//�湮�Ѱ��� �������� ���� 
	printf("%d ", g->data[v] + 1);	//�湮�Ѱ� ��� //�迭�� �ε����� �����Ͽ� +1
	for(w = 0; w < g->vertex; w++) {	
		if(g->adj_m[v][w] && !visited[w])	//������ �ְ� �湮���� �ʾҴٸ� ���� 
			DFS(g, w);
	}
} 

void BFS(Graph *g, int v) {	//������� �ʺ�켱Ž�� 
	int w;
	Queue *q = (Queue *)malloc(sizeof(Queue));
	
	init_queue(q);
	visited[v] = 1;
	printf("%d ", g->data[v] + 1);	//�迭�� �ε����� �����Ͽ� +1
	enqueue(q, v);
	
	while(!is_empty(q)) {
		v = dequeue(q);
		for(w = 0; w < g->vertex; w++) {
			if(g->adj_m[v][w] && !visited[w]) {
				visited[w] = 1;
				printf("%d ", g->data[w] + 1);	//�迭�� �ε����� �����Ͽ� +1 
				enqueue(q, w);
			}
		}
	}
}

int main(void) {
	Graph *g = (Graph *)malloc(sizeof(Graph));
	int i, vertex, edge, start_v;
	int edge_start, edge_end;
	init_graph(g);
	
	printf("������ ����, ������ ����, Ž���� ������ ��ȣ�� �Է��ϼ��� : ");
	scanf("%d %d %d", &vertex, &edge, &start_v);
	
	for(i = 0; i < vertex; i++)
		insert_vertex(g, i);
		
	for(i = 0; i < edge; i++) {
		printf("������ �����ϴ� �� ������ �Է��ϼ��� : ");
		scanf("%d %d", &edge_start, &edge_end);
		insert_edge(g, edge_start -1, edge_end -1);	//�迭�� �ε����� 0���� �����ϹǷ� 1�� ���ش� 
	}
	
	
	print_graph(g);
	printf("\n") ;
	reset_visited(g);
	printf("DFSŽ�� -> ");
	DFS(g, start_v - 1);	//�迭�� �ε����� �����Ͽ� -1 
	printf("\n");
	reset_visited(g);
	printf("BFSŽ�� -> ");
	BFS(g, start_v - 1);	//�迭�� �ε����� �����Ͽ� -1 
	printf("\n");

	
	free(g);

	return 0;
}
