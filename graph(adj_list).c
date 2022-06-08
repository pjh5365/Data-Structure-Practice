#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX 50

typedef struct graphnode{
	int data;
	struct graphnode *link;
}GraphN;

typedef struct graphlist{
	int vertex;
	GraphN *adj_list[MAX_VERTEX];
}GraphL;

void init_list(GraphL *g1) {
	int v;
	g1->vertex = 0;
	for(v = 0; v < MAX_VERTEX; v++)
		g1->adj_list[v] = NULL;
}

void insert_vertex_list(GraphL *g1, int v) {
	if(g1->vertex + 1 > MAX_VERTEX) {
		printf("그래프 정점의 갯수 초과 \n");
		return;
	}
	g1->vertex++;
}

void insert_edge_list(GraphL *g1, int start, int end) {
	if(start >= g1->vertex || end >= g1->vertex) {
		printf("그래프 정점번호 오류 \n");
		return;
	}
	
	GraphN * node = (GraphN *)malloc(sizeof(GraphN));
	node->data = end;
	node->link = g1->adj_list[start];
	g1->adj_list[start] = node;
}

void print_graph_list(GraphL *g1) {
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

int main(void) {
	int i;
	GraphL *g1 = (GraphL *)malloc(sizeof(GraphL));
	init_list(g1);
	for(i = 0; i < 4; i++)
		insert_vertex_list(g1, i);
	
	insert_edge_list(g1, 0, 1);
	insert_edge_list(g1, 1, 0);
	insert_edge_list(g1, 0, 2);	
	insert_edge_list(g1, 2, 0);
	insert_edge_list(g1, 0, 3);
	insert_edge_list(g1, 3, 0);
	insert_edge_list(g1, 1, 2);
	insert_edge_list(g1, 2, 1);
	insert_edge_list(g1, 2, 3);
	insert_edge_list(g1, 3, 2);
	
	print_graph_list(g1);
	free(g1);

	
	return 0;
}
