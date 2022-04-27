#include <stdio.h>
#include <stdlib.h>

typedef struct linked_list{
	int data;
	struct linked_list *link;
}List;

void insert_node_data(List **first, List *now, int data) {	//now�ڿ��ٰ� ���ο� ��带 �߰��ϴ� �Լ� 
	List *tmp = (List *)malloc(sizeof(List));
	tmp->data = data;
	if(now == NULL) {
		tmp->link = NULL;
		now->link = tmp;
	}
	else {
		tmp->link = now->link;
		now->link = tmp;
	}
}

void insert_node_data_first(List **first, int data) {	//ù��°��带 �����ϴ� �Լ� 

	List *tmp = (List *)malloc(sizeof(List));
	tmp->data = data;
	tmp->link = *first;	//first�� �ּҸ� �����Ѿ��ϹǷ� *�ϳ��� ����� 
	*first = tmp;
} 

int delete_node_data(List **first, List *now) {	//now���� ��带 �����ϴ� �Լ� 
	int remove;
	List *tmp;
	
	if(now == NULL){	//ù��° ��带 �����ϴ� ��� 
		tmp = (*first)->link;	//ù��° ��尡 ����Ű���ִ� ����� �ּҸ� �Ѱ���
		remove = (*first)->data;	//ù��° ����� �����Ͱ� 
		free(*first);	//ù��° ����� �Ҵ����� 
		*first = tmp; 
	}
	else {
		remove = now->link->data;
		tmp = now->link->link;
		free(now->link);	//������ ����� �Ҵ����� 
		now->link = tmp;
	}
	return remove;
}

void print_node(List **first) {		//���Ḯ��Ʈ�� ����ϴ� �Լ� 
	List *p;
	for(p = *first; p != NULL; p = p->link)
		printf("[%2d]-> ", p->data);
	printf("\n");
}

int main(void) {
	List *first, *now;	//ù��° ��带 ����ų �����ͺ����� ���� ��ġ�� ��Ÿ�� �����ͺ��� 
	first = NULL;
	now = NULL;
	
	insert_node_data_first(&first, 1);
	insert_node_data_first(&first, 2);
	insert_node_data_first(&first, 3);
	insert_node_data_first(&first, 4);
	insert_node_data_first(&first, 5); 

	print_node(&first);
	
	printf("\n\n%d\n\n", delete_node_data(&first, now));
	
	print_node(&first);
	
	return 0;
}
