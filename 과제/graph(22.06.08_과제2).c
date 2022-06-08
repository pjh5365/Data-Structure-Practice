#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX 50
#define MAX_QUEUE_SIZE 50

typedef struct graph {	//그래프의 구조체 선언 
	int vertex;
	int data[MAX_VERTEX];	//정점의 데이터를 담을 배열 
	int adj_m[MAX_VERTEX][MAX_VERTEX];
}Graph;

typedef struct queue {
	int queuedata[MAX_QUEUE_SIZE];
	int front, rear;
}Queue;

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
		g->data[g->vertex] = i;
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
		printf("%d \t", g->data[i] + 1);	//배열의 인덱스를 생각하여 +1
		for(j = 0; j < g->vertex; j++)
			printf("[%2d] ", g->adj_m[i][j]);
		
		printf("\n");
	}
} 

void DFS(Graph *g, int v) {	//인접행렬 깊이우선탐색 
	int w;
	visited[v] = 1;	//방문한곳은 참값으로 변경 
	printf("%d ", g->data[v] + 1);	//방문한곳 출력 //배열의 인덱스를 생각하여 +1
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
	printf("%d ", g->data[v] + 1);	//배열의 인덱스를 생각하여 +1
	enqueue(q, v);
	
	while(!is_empty(q)) {
		v = dequeue(q);
		for(w = 0; w < g->vertex; w++) {
			if(g->adj_m[v][w] && !visited[w]) {
				visited[w] = 1;
				printf("%d ", g->data[w] + 1);	//배열의 인덱스를 생각하여 +1 
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
	
	printf("정점의 개수, 간선의 개수, 탐색을 시작할 번호를 입력하세요 : ");
	scanf("%d %d %d", &vertex, &edge, &start_v);
	
	for(i = 0; i < vertex; i++)
		insert_vertex(g, i);
		
	for(i = 0; i < edge; i++) {
		printf("간선이 연결하는 두 정점을 입력하세요 : ");
		scanf("%d %d", &edge_start, &edge_end);
		insert_edge(g, edge_start -1, edge_end -1);	//배열의 인덱스는 0부터 시작하므로 1씩 빼준다 
	}
	
	
	print_graph(g);
	printf("\n") ;
	reset_visited(g);
	printf("DFS탐색 -> ");
	DFS(g, start_v - 1);	//배열의 인덱스를 생각하여 -1 
	printf("\n");
	reset_visited(g);
	printf("BFS탐색 -> ");
	BFS(g, start_v - 1);	//배열의 인덱스를 생각하여 -1 
	printf("\n");

	
	free(g);

	return 0;
}
