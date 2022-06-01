#include <stdio.h>
#include <stdlib.h>
#define MAX 100

int heap[MAX];	//히프의 선언 
int heap_size;	//히프의 크기 

void insert_node(int key) {	//최대히프 삽입연산 
	int i;
	i = ++(heap_size);
	
	while((i != 1) && (key > heap[i / 2])) {	// 현재 위치가 루트가 아니고 키값이 부모노드보다 클때 동안 반복 
		heap[i] = heap[i / 2];	//부모노드와의 교환
		i /= 2; 
	}
	heap[i] = key;
}

int delete_node(void) {	//최대히프 삭제연산 
	int parent, child;
	int key, tmp;
	
	key = heap[1];	//루트의 값 반환
	tmp = heap[heap_size--];	//히프에서 마지막 노드가져오고 사이즈--
	parent = 1;	//루트를 가리키도록 
	child = 2;	//자식노드중 첫번째를 가르키도록 
	
	while(child <= heap_size) {
		if((child < heap_size) && heap[child] < heap[child + 1]) 	//현재노드의 자식중 큰 값을 찾기위함 
			child++;
		if(tmp >= heap[child]) //마지막에 있었던 노드가 가장 클경우(교환이 필요없을경우) 
			break;
		
		heap[parent] = heap[child];	//부모노드와 자식노드의 교환 (처음이라면 루트에 가장 큰 자식노드의값 삽입 이후 부모자식간의 교환) 
		parent = child;	//자식노드로 이동 
		child *= 2;	//자식노드의 자식노드로 이동 
	} 
	heap[parent] = tmp;	
	return key;
}

int main(void) {
	insert_node(10);
	insert_node(5);
	insert_node(30);
	
	printf("<%d> ", delete_node());
	printf("<%d> ", delete_node());
	printf("<%d> ", delete_node());
	
	
	return 0;
}
