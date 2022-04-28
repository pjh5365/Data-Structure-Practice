#include <stdio.h>
#include <stdlib.h>

typedef struct double_linked_list {
	int data;
	struct double_linked_list *llink;	//���ʳ��� ����� ��ũ 
	struct double_linked_list *rlink;	//�����ʳ��� ����� ��ũ 
}Node;

void insert_data(Node **dlist, Node *now, int data) {	//now�ڿ� ���ο� ��带 �߰��ϴ� �Լ� 
	Node *tmp = (Node *)malloc(sizeof(Node));
	
	tmp->data = data;
	if(now == NULL) {	//ù��° ��忡 �߰��Ҷ� 
		tmp->llink = NULL;
		tmp->rlink = *dlist;
		*dlist = tmp;
	}
	else {
		tmp->rlink = now->rlink;
		tmp->llink = now;
	}
}

int delete_data(Node **dlist, Node *now) {	//now�ڿ� �ִ� ��带 �����ϴ� �Լ� 
	int remove;
	Node *tmp;
	
	if(now == NULL) {	//ù��° ��带 �����Ҷ� 
		tmp = *dlist;
		*dlist = tmp->rlink;
		tmp->rlink->llink = NULL;
		remove = tmp->data;
		free(tmp);	//������ ����� �Ҵ����� 
	} 
	else {
		tmp = now->rlink;
		now->rlink = tmp->rlink;
		tmp->rlink->llink = now;
		remove = tmp->data;
		free(tmp);	//������ ����� �Ҵ����� 
	}
	
	return remove;
}

void print_node(Node **dlist) {
	Node *p;
	for(p = *dlist; p != NULL; p = p->rlink)
		printf("[%d]-> ", p->data);
	printf("\n");
}

int main(void) {
	
	Node *dlist;
	Node *now;
	dlist = NULL;
	now = NULL;
	
	insert_data(&dlist, now, 1);
	insert_data(&dlist, now, 2);
	insert_data(&dlist, now, 3);
	insert_data(&dlist, now, 4);
	
	print_node(&dlist);
	printf("\n\n%d\n\n", delete_data(&dlist, now));
	print_node(&dlist);
	
	return 0;
}
