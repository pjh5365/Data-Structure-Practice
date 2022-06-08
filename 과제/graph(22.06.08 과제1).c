#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX 50
#define MAX_QUEUE_SIZE 50

typedef struct graph {	//그래프의 구조체 선언 
	int vertex;
	char data[MAX_VERTEX];	//정점의 데이터를 담을 배열 
	int adj_m[MAX_VERTEX][MAX_VERTEX];
}Graph;

typedef struct queue {
	int queuedata[MAX_QUEUE_SIZE];
	int front, rear;
}Queue;

typedef struct graphnode{	//인접리스트의 노드 구조체 
	int data;
	struct graphnode *link;
}GraphN;

typedef struct graphlist{	//인접리스트의 구조체 
	int vertex;
	GraphN *adj_list[MAX_VERTEX];
}GraphL;

void init_list(GraphL *g1) {	//인접리스트 초기화 
	int v;
	g1->vertex = 0;
	for(v = 0; v < MAX_VERTEX; v++)
		g1->adj_list[v] = NULL;
}

void insert_vertex_list(GraphL *g1, int v) {	//인접리스트 정점생성 
	if(g1->vertex + 1 > MAX_VERTEX) {
		printf("그래프 정점의 갯수 초과 \n");
		return;
	}
	g1->vertex++;
}

void insert_edge_list(GraphL *g1, int start, int end) {	//인접리스트 간선 생성함수 
	if(start >= g1->vertex || end >= g1->vertex) {
		printf("그래프 정점번호 오류 \n");
		return;
	}
	
	GraphN * node = (GraphN *)malloc(sizeof(GraphN));
	node->data = end;
	node->link = g1->adj_list[start];
	g1->adj_list[start] = node;
}

void print_graph_list(GraphL *g1) {	//인접리스트 출력함수 
	int i;
	for(i = 0; i < g1->vertex; i++) {
		GraphN *p = g1->adj_list[i];
		printf("정점 %c의 인접리스트 ", 'A' + i);
		while(p != NULL) {
			printf("-> %c ", 'A' + p->data);
			p = p->link;
		}
		printf("\n");
	}
}

int is_empty(Queue *q) {	//큐의 공백검사함수 
	return (q->front == q->rear);
}

int is_full(Queue *q) {	//큐의 포화상태검사함수 
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

void init_queue(Queue *q) {	//큐 초기화함수 
	q->front = q->rear = 0;
}

void enqueue(Queue *q, char data) {	//큐의 삽입연산 
	if(is_full(q))
		printf("큐가 포화상태입니다. \n");
		
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->queuedata[q->rear] = data;
}

char dequeue(Queue *q) {	//큐의 삭제연산 
	if(is_empty(q))
		printf("큐가 공백상태입니다. \n");
	
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->queuedata[q->front];
}

int visited[MAX_VERTEX];	//방문한 정점을 담을 배열

void reset_visited(Graph *g) {	//방문한 정점을 담을 배열 초기화 
	int i;
	for(i = 0; i < g->vertex; i++)
		visited[i] = 0;
} 

void init_graph(Graph *g) {	//그래프를 초기화 하는 함수 
	int i, j;
	g->vertex = 0;
	
	for(i = 0; i < MAX_VERTEX; i++) {
		for(j = 0; j < MAX_VERTEX; j++)
			g->adj_m[i][j] = 0;
	}
}

void insert_vertex(Graph *g, int i) {	//그래프의 정점을 추가하는 함수 
		if(g->vertex +1 > MAX_VERTEX) {
			printf("정점의 갯수 초과 \n");
			return;
		}
		g->data[g->vertex] = 'A' + i;
		g->vertex++; 
}

void insert_edge(Graph *g, int start, int end) {	//무방향 그래프의 간선 삽입 
	if(start >= g->vertex || end >= g->vertex) {
		printf("정점의 번호 오류 \n");
		return;
	}
	g->adj_m[start][end] = 1;
	g->adj_m[end][start] = 1;
}

void print_graph(Graph *g) {	//인접행렬 출력함수 
	int i, j;
	
	printf("%d \n", g->vertex);
		
	for(i = 0; i < g->vertex; i++) {
		printf("%c \t", g->data[i]);
		for(j = 0; j < g->vertex; j++)
			printf("[%2d] ", g->adj_m[i][j]);
		
		printf("\n");
	}
} 

void DFS(Graph *g, int v) {	//인접행렬 깊이우선탐색 
	int w;
	visited[v] = 1;	//방문한곳은 참값으로 변경 
	printf("%c ", g->data[v]);	//방문한곳 출력 
	for(w = 0; w < g->vertex; w++) {	
		if(g->adj_m[v][w] && !visited[w])	//간선이 있고 방문하지 않았다면 실행 
			DFS(g, w);
	}
} 

void BFS(Graph *g, int v) {	//인접행렬 너비우선탐색 
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
	printf("인접행렬 출력 \n\n") ;
	print_graph(g);	//인접행렬 출력 
	printf("\n") ;
	printf("인접리스트 출력 \n\n") ;
	print_graph_list(g1);	//인접리스트 출력 
	printf("\n");
	
	reset_visited(g);
	printf("DFS탐색(인접행렬) -> ");
	DFS(g, 0);
	printf("\n");
	
	reset_visited(g);
	printf("BFS탐색(인접리스트) -> ");
	BFS_list(g1, 0);
	printf("\n");
	
	
	free(g);
	free(g1);
	return 0;
}
