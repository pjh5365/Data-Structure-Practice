#include <stdio.h>
#include <stdlib.h>

typedef struct phone{
	char num[20];	// -�� ������ ��ȭ��ȣ�� �ޱ����� 
	char name[10]; 	
	struct phone *link;
}P_node;

void insert_data(P_node *head, char num[], char name[]) {	//������ ��������� �ڿ� ���ο� ��带 ���� 
	P_node *new_node = (P_node *)malloc(sizeof(P_node));	//���ο� ��� �����Ҵ����� ���� 
	strcpy(new_node->num, num);	//��ȭ��ȣ�� ���ο� ��忡 ���� 
	strcpy(new_node->name, name);	//�̸��� ���ο� ��忡 ���� 
	new_node->link = head->link;	//���ο� ��带 ��� ���ڿ��ٰ� ���� 
	head->link = new_node;	//����尡 ����Ű�� ���� ���ο� ��尡 ����Ű�� ���� ���� 
}

void print_node(P_node *head) {
	P_node *tmp;	//��带 Ž���� �����ͺ���
	for(tmp = head->link; tmp != NULL; tmp = tmp->link)
		printf("%s \t\t %s \n", tmp->name, tmp->num);
	printf("\n");
}

int main(void) {
	int count, i;
	char name[10];
	char num[20];
	
	P_node *head =(P_node *)malloc(sizeof(P_node));	//��������ͻ��� 
	head->link = NULL;	//����������� ��ũ�� �η� �ʱ�ȭ 
	
	printf("�ּ��� ������ �Է��ϼ��� : ");
	scanf("%d", &count);
	
	for(i = 0; i < count; i++) {
		printf("�̸��� �Է��ϼ��� : ");
		scanf("%s", name);
		printf("��ȣ�� �Է��ϼ��� : ");
		scanf("%s", num);
		insert_data(head, num, name);
	}
	
	printf("================================\n");
	printf("�̸� \t\t ��ȭ��ȣ\n");
	printf("================================\n");
	
	print_node(head);
	
	free(head);
	
	return 0;
}
