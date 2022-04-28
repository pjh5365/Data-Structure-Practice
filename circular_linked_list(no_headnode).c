#include <stdio.h>
#include <stdlib.h>

typedef struct circular_linked_list {
	int data;
	struct circular_linked_list *link;
}C_node;

void insert_data_fisrt(C_node **clist, int data) {
	C_node *tmp = (C_node *)malloc(sizeof(C_node));
	tmp->data = data;
	
	if(*clist == NULL) {	//첫번째 노드를 생성할때 
		tmp->link = tmp;	//원형으로 만들기 위해 
		*clist = tmp->link; 
	}
	else {	//첫번째에 새로운 노드를 생성 
		tmp->link = (*clist)->link;
		(*clist)->link = tmp;
	}
}

int delete_node_first(C_node **clist) {	//첫번째 노드를 삭제하는함수 
	C_node *tmp;
	int remove;
	
	tmp = (*clist)->link;
	remove = tmp->data;
	(*clist)->link = tmp->link;
	
	free(tmp);
	return remove;
} 

void print_node(C_node **clist) {
	C_node *p = (*clist)->link;
	while(1) {
		printf("[%d]-> ", p->data);
		p = p->link;
		
		if(p == *clist) {	//다시 처음으로 돌아왔을때 
			printf("[%d]-> ", p->data);
			break;
		}
	}
}

int main(void) {
	C_node *clist;	//리스트의 마지막 리스트를 가르키는 변수 
	clist = NULL;
	
	insert_data_fisrt(&clist, 1);
	insert_data_fisrt(&clist, 2);
	insert_data_fisrt(&clist, 3);
	insert_data_fisrt(&clist, 4);
	insert_data_fisrt(&clist, 5);
	
	print_node(&clist);
	
	printf("\n\n%d\n\n", delete_node_first(&clist));
	print_node(&clist);
	
	return 0;
}
