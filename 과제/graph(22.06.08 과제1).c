#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX 50
#define MAX_QUEUE_SIZE 50

typedef struct graph {	//�׷����� ����ü ���� 
	int vertex;
	char data[MAX_VERTEX];	//������ �����͸� ���� �迭 
	int adj_m[MAX_VERTEX][MAX_VERTEX];
}Graph;

typedef struct queue {
	int queuedata[MAX_QUEUE_SIZE];
	int front, rear;
}Queue;

typedef struct graphnode{	//��������Ʈ�� ��� ����ü 
	int data;
	struct graphnode *link;
}GraphN;

typedef struct graphlist{	//��������Ʈ�� ����ü 
	int vertex;
	GraphN *adj_list[MAX_VERTEX];
}GraphL;

void init_list(GraphL *g1) {	//��������Ʈ �ʱ�ȭ 
	int v;
	g1->vertex = 0;
	for(v = 0; v < MAX_VERTEX; v++)
		g1->adj_list[v] = NULL;
}

void insert_vertex_list(GraphL *g1, int v) {	//��������Ʈ �������� 
	if(g1->vertex + 1 > MAX_VERTEX) {
		printf("�׷��� ������ ���� �ʰ� \n");
		return;
	}
	g1->vertex++;
}

void insert_edge_list(GraphL *g1, int start, int end) {	//��������Ʈ ���� �����Լ� 
	if(start >= g1->vertex || end >= g1->vertex) {
		printf("�׷��� ������ȣ ���� \n");
		return;
	}
	
	GraphN * node = (GraphN *)malloc(sizeof(GraphN));
	node->data = end;
	node->link = g1->adj_list[start];
	g1->adj_list[start] = node;
}

void print_graph_list(GraphL *g1) {	//��������Ʈ ����Լ� 
	int i;
	for(i = 0; i < g1->vertex; i++) {
		GraphN *p = g1->adj_list[i];
		printf("���� %c�� ��������Ʈ ", 'A' + i);
		while(p != NULL) {
			printf("-> %c ", 'A' + p->data);
			p = p->link;
		}
		printf("\n");
	}
}

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
		g->data[g->vertex] = 'A' + i;
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
		printf("%c \t", g->data[i]);
		for(j = 0; j < g->vertex; j++)
			printf("[%2d] ", g->adj_m[i][j]);
		
		printf("\n");
	}
} 

void DFS(Graph *g, int v) {	//������� ���̿켱Ž�� 
	int w;
	visited[v] = 1;	//�湮�Ѱ��� �������� ���� 
	printf("%c ", g->data[v]);	//�湮�Ѱ� ��� 
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
	printf("%c ", g->data[v]);
	enqueue(q, v);
	
	while(!is_empty(q)) {
		v = dequeue(q);
		for(w = 0; w < g->vertex; w++) {
			if(g->adj_m[v][w] && !visited[w]) {
				visited[w] = 1;
				printf("%c ", g->data[w]);
				enqueue(q, w);
			}
		}
	}
	free(q);
}

void BFS_list(GraphL *g1, int v) {
	GraphN *w;
	Queue *q = (Queue *)malloc(sizeof(Queue));
	
	init_queue(q);
	visited[v] = 1;
	printf("%c ", 'A' + v);
	enqueue(q, v);
	while(!is_empty(q)) {
		v = dequeue(q);
		for( w = g1->adj_list[v]; w; w = w->link) {
			if(!visited[w->data]) {
				visited[w->data] = 1;
				printf("%c ", 'A' + w->data);
				enqueue(q, w->data);
			}
		}
	}
	free(g1);
}

int main(void) {
	Graph *g = (Graph *)malloc(sizeof(Graph));
	int i;
	init_graph(g);
	
	for(i = 0; i < 8; i++)
		insert_vertex(g, i);
		
	insert_edge(g, 0, 1);
	insert_edge(g, 0, 2);
	insert_edge(g, 1, 3);
	insert_edge(g, 2, 3);
	insert_edge(g, 2, 4);
	insert_edge(g, 3, 5);
	insert_edge(g, 4, 6);
	insert_edge(g, 4, 7);
	insert_edge(g, 6, 7);
	
	GraphL *g1 = (GraphL *)malloc(sizeof(GraphL));
	init_list(g1);
	for(i = 0; i < 8; i++)
		insert_vertex_list(g1, i);
	
	insert_edge_list(g1, 0, 2);
	insert_edge_list(g1, 0, 1);
	insert_edge_list(g1, 1, 3);
	insert_edge_list(g1, 1, 0);
	insert_edge_list(g1, 2, 4);
	insert_edge_list(g1, 2, 3);
	insert_edge_list(g1, 2, 0);
	insert_edge_list(g1, 3, 5);
	insert_edge_list(g1, 3, 2);
	insert_edge_list(g1, 3, 1);
	insert_edge_list(g1, 4, 7);
	insert_edge_list(g1, 4, 6);
	insert_edge_list(g1, 4, 2);
	insert_edge_list(g1, 5, 3);
	insert_edge_list(g1, 6, 7);	
	insert_edge_list(g1, 6, 4);
	insert_edge_list(g1, 7, 6);
	insert_edge_list(g1, 7, 4);
	
	printf("\n") ;
	printf("������� ��� \n\n") ;
	print_graph(g);	//������� ��� 
	printf("\n") ;
	printf("��������Ʈ ��� \n\n") ;
	print_graph_list(g1);	//��������Ʈ ��� 
	printf("\n");
	
	reset_visited(g);
	printf("DFSŽ��(�������) -> ");
	DFS(g, 0);
	printf("\n");
	
	reset_visited(g);
	printf("BFSŽ��(��������Ʈ) -> ");
	BFS_list(g1, 0);
	printf("\n");
	
	
	free(g);
	free(g1);
	return 0;
}
