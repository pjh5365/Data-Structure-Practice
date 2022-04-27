#include <stdio.h>
#include <stdlib.h>

typedef struct linked_list{
	int data;
	struct linked_list *link;
}List;

void insert_node_data(List **first, List *now, int data) {	//now뒤에다가 새로운 노드를 추가하는 함수 
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

void insert_node_data_first(List **first, int data) {	//첫번째노드를 생성하는 함수 

	List *tmp = (List *)malloc(sizeof(List));
	tmp->data = data;
	tmp->link = *first;	//first의 주소를 가르켜야하므로 *하나만 써야함 
	*first = tmp;
} 

int delete_node_data(List **first, List *now) {	//now다음 노드를 삭제하는 함수 
	int remove;
	List *tmp;
	
	if(now == NULL){	//첫번째 노드를 삭제하는 경우 
		tmp = (*first)->link;	//첫번째 노드가 가르키고있던 노드의 주소를 넘겨줌
		remove = (*first)->data;	//첫번째 노드의 데이터값 
		free(*first);	//첫번째 노드의 할당해제 
		*first = tmp; 
	}
	else {
		remove = now->link->data;
		tmp = now->link->link;
		free(now->link);	//삭제할 노드의 할당해제 
		now->link = tmp;
	}
	return remove;
}

void print_node(List **first) {		//연결리스트를 출력하는 함수 
	List *p;
	for(p = *first; p != NULL; p = p->link)
		printf("[%2d]-> ", p->data);
	printf("\n");
}

int main(void) {
	List *first, *now;	//첫번째 노드를 가르킬 포인터변수와 현재 위치를 나타낼 포인터변수 
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
