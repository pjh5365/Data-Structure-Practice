#include <stdio.h>
#include <stdlib.h>

typedef struct phone{
	char num[20];	// -를 포함한 전화번호를 받기위함 
	char name[10]; 	
	struct phone *link;
}P_node;

void insert_data(P_node *head, char num[], char name[]) {	//무조건 헤드포인터 뒤에 새로운 노드를 생성 
	P_node *new_node = (P_node *)malloc(sizeof(P_node));	//새로운 노드 동적할당으로 생성 
	strcpy(new_node->num, num);	//전화번호를 새로운 노드에 저장 
	strcpy(new_node->name, name);	//이름을 새로운 노드에 저장 
	new_node->link = head->link;	//새로운 노드를 헤드 노드뒤에다가 연결 
	head->link = new_node;	//헤드노드가 가르키던 값을 새로운 노드가 가르키게 만들어서 연결 
}

void print_node(P_node *head) {
	P_node *tmp;	//노드를 탐색할 포인터변수
	for(tmp = head->link; tmp != NULL; tmp = tmp->link)
		printf("%s \t\t %s \n", tmp->name, tmp->num);
	printf("\n");
}

int main(void) {
	int count, i;
	char name[10];
	char num[20];
	
	P_node *head =(P_node *)malloc(sizeof(P_node));	//헤드포인터생성 
	head->link = NULL;	//헤드포인터의 링크를 널로 초기화 
	
	printf("주소의 갯수를 입력하세요 : ");
	scanf("%d", &count);
	
	for(i = 0; i < count; i++) {
		printf("이름을 입력하세요 : ");
		scanf("%s", name);
		printf("번호를 입력하세요 : ");
		scanf("%s", num);
		insert_data(head, num, name);
	}
	
	printf("================================\n");
	printf("이름 \t\t 전화번호\n");
	printf("================================\n");
	
	print_node(head);
	
	free(head);
	
	return 0;
}
