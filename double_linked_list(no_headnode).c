#include <stdio.h>
#include <stdlib.h>

typedef struct double_linked_list {
	int data;
	struct double_linked_list *llink;	//왼쪽노드와 연결된 링크 
	struct double_linked_list *rlink;	//오른쪽노드와 연결된 링크 
}Node;

void insert_data(Node **dlist, Node *now, int data) {	//now뒤에 새로운 노드를 추가하는 함수 
	Node *tmp = (Node *)malloc(sizeof(Node));
	
	tmp->data = data;
	if(now == NULL) {	//첫번째 노드에 추가할때 
		tmp->llink = NULL;
		tmp->rlink = *dlist;
		*dlist = tmp;
	}
	else {
		tmp->rlink = now->rlink;
		tmp->llink = now;
	}
}

int delete_data(Node **dlist, Node *now) {	//now뒤에 있는 노드를 삭제하는 함수 
	int remove;
	Node *tmp;
	
	if(now == NULL) {	//첫번째 노드를 삭제할때 
		tmp = *dlist;
		*dlist = tmp->rlink;
		tmp->rlink->llink = NULL;
		remove = tmp->data;
		free(tmp);	//삭제할 노드의 할당해제 
	} 
	else {
		tmp = now->rlink;
		now->rlink = tmp->rlink;
		tmp->rlink->llink = now;
		remove = tmp->data;
		free(tmp);	//삭제할 노드의 할당해제 
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
