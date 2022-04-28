#include <stdio.h>
#include <stdlib.h>

typedef struct circular_linked_list {
	int data;
	struct circular_linked_list *link;
}C_node;

void insert_data_fisrt(C_node **clist, int data) {
	C_node *tmp = (C_node *)malloc(sizeof(C_node));
	tmp->data = data;
	
	if(*clist == NULL) {	//ù��° ��带 �����Ҷ� 
		tmp->link = tmp;	//�������� ����� ���� 
		*clist = tmp->link; 
	}
	else {	//ù��°�� ���ο� ��带 ���� 
		tmp->link = (*clist)->link;
		(*clist)->link = tmp;
	}
}

int delete_node_first(C_node **clist) {	//ù��° ��带 �����ϴ��Լ� 
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
		
		if(p == *clist) {	//�ٽ� ó������ ���ƿ����� 
			printf("[%d]-> ", p->data);
			break;
		}
	}
}

int main(void) {
	C_node *clist;	//����Ʈ�� ������ ����Ʈ�� ����Ű�� ���� 
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
