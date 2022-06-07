#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX 50

typedef struct graph{
	int n;	//정점의 갯수
	int adj[MAX_VERTEX][MAX_VERTEX]; 	//그래프를 담을 행렬 
}Graph;

void init_graph(Graph * g) {	//그래프를 초기화 하는 함수 
	int i, j;
	g->n = 0;
	for(i = 0; i < MAX_VERTEX; i++) {
		for(j = 0; j < MAX_VERTEX; j++)
			g->adj[i][j] = 0;
	}
}

void insert_vertex(Graph *g) {	//정점의 갯수를 올리는 함수 
	if(g->n +1 > MAX_VERTEX) {
		printf("그래프 정점의 갯수 초과 \n");
		return;
	}
	g->n++;
}

void insert_edge(Graph * g, int start, int end) {	//무방향 그래프의 간선 삽입 	
	if(start >= g->n || end >= g->n) {
		printf("그래프 정점 번호 오류 \n");
		return;
	}
	
	g->adj[start][end] = 1; 
	g->adj[end][start] = 1;
}

void print_graph(Graph *g) {
	int i, j;
	
	for(i = 0; i < g->n; i++) {
		for(j = 0; j < g->n; j++)
			printf("[%2d] ", g->adj[i][j]);
		
		printf("\n");
	}
}

int main(void) {
	Graph *g = (Graph *)malloc(sizeof(Graph));
	init_graph(g);
	int i;
	
	for(i = 0; i < 4; i++)
		insert_vertex(g);
	
	insert_edge(g, 0, 1);
	insert_edge(g, 0, 2);
	insert_edge(g, 0, 3);
	insert_edge(g, 1, 2);
	insert_edge(g, 2, 3);
	
	print_graph(g);
	
	return 0;
}
