#include <stdio.h>
#include <stdlib.h>
#define MAX 100

int heap[MAX];	//������ ���� 
int heap_size;	//������ ũ�� 

void insert_node(int key) {	//�ִ����� ���Կ��� 
	int i;
	i = ++(heap_size);
	
	while((i != 1) && (key > heap[i / 2])) {	// ���� ��ġ�� ��Ʈ�� �ƴϰ� Ű���� �θ��庸�� Ŭ�� ���� �ݺ� 
		heap[i] = heap[i / 2];	//�θ������ ��ȯ
		i /= 2; 
	}
	heap[i] = key;
}

int delete_node(void) {	//�ִ����� �������� 
	int parent, child;
	int key, tmp;
	
	key = heap[1];	//��Ʈ�� �� ��ȯ
	tmp = heap[heap_size--];	//�������� ������ ��尡������ ������--
	parent = 1;	//��Ʈ�� ����Ű���� 
	child = 2;	//�ڽĳ���� ù��°�� ����Ű���� 
	
	while(child <= heap_size) {
		if((child < heap_size) && heap[child] < heap[child + 1]) 	//�������� �ڽ��� ū ���� ã������ 
			child++;
		if(tmp >= heap[child]) //�������� �־��� ��尡 ���� Ŭ���(��ȯ�� �ʿ�������) 
			break;
		
		heap[parent] = heap[child];	//�θ���� �ڽĳ���� ��ȯ (ó���̶�� ��Ʈ�� ���� ū �ڽĳ���ǰ� ���� ���� �θ��ڽİ��� ��ȯ) 
		parent = child;	//�ڽĳ��� �̵� 
		child *= 2;	//�ڽĳ���� �ڽĳ��� �̵� 
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
