#include <stdio.h>
#include <stdlib.h>

typedef struct linked_list {
	
	int data;
	struct linked_list *link;
	
}Node;

void insert_data_first(Node *head, int data) {	//헤드노드 바로 뒤에 노드를 추가하는 함수 

	Node *new_node = (Node *)malloc(sizeof(Node));
	new_node->data = data;
	
	if(head->link == NULL) {	//첫번째 노드를 추가할때 
		head->link = new_node;
		new_node->link = NULL;
	}
	else {
		new_node->link = head->link;
		head->link = new_node;
	}
}

int delete_node_first(Node *head) {	//첫번째 노드를 삭제하는 함수 
	
	int remove;
	Node *tmp;
	tmp = head->link;
	remove = tmp->data;
	head->link = tmp->link;
	free(tmp);
	return remove; 
	
}

void print_node(Node *head) {	//전체노드를 출력하는 함수 
	
	Node *p;
	
	for(p = head->link; p != NULL; p = p->link)
		printf("[%d]-> ", p->data);
	printf("\n");
	
}

int main(void) {
	
	Node *head = (Node *)malloc(sizeof(Node));
	head->link = NULL;
	
	insert_data_first(head, 1);
	insert_data_first(head, 2);
	insert_data_first(head, 3);
	insert_data_first(head, 4);
	insert_data_first(head, 5);
	
	print_node(head);
	printf("\n\n%d\n\n", delete_node_first(head));
	print_node(head);
	
	
	free(head); 
	return 0;
	
}
