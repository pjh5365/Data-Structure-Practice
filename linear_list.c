#include <stdio.h>
#define MAX 10


typedef struct linear_list{
	int data[MAX];
	int length;
}List;

void insert_data(List *A, int i, int data) {	//i번째 배열에 데이터를 넣는 함수 
	int j;
	for(j = A->length; j > i; j--) 
		A->data[j+1] = A->data[j];
	
	A->data[i] = data;
	A->length++;
}

void insert_data_L(List *A, int data) {	//마지막 배열에 데이터를 넣는 함수 
	A->data[++(A->length)] = data;
}

int delete_data(List *A, int i) {	//i번째 원소를 삭제하는 함수 
	int j;
	int tmp;
	tmp = A->data[i];
	
	for(j = i; j < A->length; j++)
		A->data[j] = A->data[j+1];
	
	A->length--;
	return tmp;
}

int main(void) {
	List A;
	A.length = -1;	//순차리스트를 초기화 
	int i;
	
	insert_data_L(&A, 123);
	insert_data_L(&A, 456);
	
	printf("\n\n%d\n\n", delete_data(&A, 1));
	
	for(i = 0; i <= A.length; i++)
		printf("[%d] ", A.data[i]);
	
}
