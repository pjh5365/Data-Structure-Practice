#include <stdio.h>
#include <stdlib.h>

typedef struct stack {
	int s_col[65];	//0�� ������ŭ���� 
	int s_row[65];
	int top;
}Stack;

void load_data(int *col, int *row, int maze[][20]);	//�̷θ� �ҷ����� �Լ� 
void mazeFind(Stack *s, int col, int row, int maze[][20]);
void push(Stack *s, int i, int j);

int main(void) {
	Stack s;
	s.top = -1;	//�����ʱ�ȭ
	
	FILE *fp = fopen("maze-pjh.out", "a");	//�Լ����� ��������Ƿ� w�� �θ��� ������ ���� 
	if(fp == NULL) {
		printf("���Ͽ��¿��� \n");
		return -1;
	}
	
	int col;
	int row;
	int maze[15][20];
	int i, j;
	
	load_data(&col, &row, maze);
	
	printf("��踦 ������ �̷��� ũ�� \n");
	printf("�� : %d �� : %d \n", col, row);
	printf("�̷���� (1�� �� 0 �� �� �Ա���maze[1][1], �ⱸ�� maze[11][15]) \n\n") ;
	for(i = 0; i < col; i++) {
		for(j = 0; j < row; j++) {
			printf("%d ", maze[i][j]);
		}
		printf("\n");
	}
	
	mazeFind(&s, col, row, maze);
	printf("\n\n�ּҰ�� ���\n\n");
	fprintf(fp, "\n\n�ּҰ�� ���\n\n"); 
	for(i = 0; i <= s.top; i++) {
		printf("%d. [%d, %d] \n", i+1, s.s_col[i], s.s_row[i]);
		fprintf(fp, "%d. [%d, %d] \n", i+1, s.s_col[i], s.s_row[i]);	
	}
	fclose(fp);
	return 0;
}

void push(Stack *s, int i, int j) {
	s->top++;
	s->s_col[s->top] = i;
	s->s_row[s->top] = j;
}

void load_data(int *col, int *row, int maze[][20]) {
	FILE *fp = fopen("maze-pjh.map", "r");
	
	int i = 0, j = 0;	//�̷θ� ������� ����
	int input;
	
	if(fp == NULL) {
		printf("���Ͽ��¿��� \n");
		return -1;
	}
	fscanf(fp, "%d" "%d", col, row);
	while(!feof(fp)) {
		fscanf(fp, "%d", &input);
		maze[i][j] = input;
		j++;
		if(j == (*row)) {
			j = 0;
			i++;
		}
	}
	fclose(fp);
}

void mazeFind(Stack *s, int col, int row, int maze[][20]) {
	
	FILE *fp = fopen("maze-pjh.out", "w");
	if(fp == NULL) {
		printf("���Ͽ��¿��� \n");
		return -1;
	}
	
	int i = 1, j = 1;
	printf("\n\n\n�̷� ã�� ����\n\n\n");
	fprintf(fp, "�̷� ã�� ����\n\n\n");
	printf("[1, 1]���� ���� \n");
	fprintf(fp, "[1, 1]���� ���� \n");
	
	while(1)  {
		if(maze[i-1][j] == 0) {
			maze[i-1][j] = 1;	//Ž���� ��δ� 1�� ǥ�� 
			push(s, i, j);
			i--;
			printf("[%d, %d]�� �̵� \n", i, j);
			fprintf(fp, "[%d, %d]�� �̵� \n", i, j);
		}
		else if(maze[i-1][j+1] == 0) {
			maze[i-1][j+1] = 1;	//Ž���� ��δ� 1�� ǥ��
			push(s, i, j);
			i--;
			j++;
			printf("[%d, %d]�� �̵� \n", i, j);
			fprintf(fp, "[%d, %d]�� �̵� \n", i, j);
		}
		else if(maze[i][j+1] == 0) {
			maze[i][j+1] = 1;	//Ž���� ��δ� 1�� ǥ��
			push(s, i, j);
			j++;
			printf("[%d, %d]�� �̵� \n", i, j);
			fprintf(fp, "[%d, %d]�� �̵� \n", i, j);
		}
		else if(maze[i+1][j+1] == 0) {
			maze[i+1][j+1] = 1;	//Ž���� ��δ� 1�� ǥ��
			push(s, i, j);
			i++;
			j++;
			printf("[%d, %d]�� �̵� \n", i, j);
			fprintf(fp, "[%d, %d]�� �̵� \n", i, j);
		}
		else if(maze[i+1][j] == 0) {
			maze[i+1][j] = 1;	//Ž���� ��δ� 1�� ǥ��
			push(s, i, j);
			i++;
			printf("[%d, %d]�� �̵� \n", i, j);
			fprintf(fp, "[%d, %d]�� �̵� \n", i, j);
		}
		else if(maze[i+1][j-1] == 0) {
			maze[i+1][j-1] = 1;	//Ž���� ��δ� 1�� ǥ��
			push(s, i, j);
			i++;
			j--;
			printf("[%d, %d]�� �̵� \n", i, j);
			fprintf(fp, "[%d, %d]�� �̵� \n", i, j);
		}
		else if(maze[i][j-1] == 0) {
			maze[i][j-1] = 1;	//Ž���� ��δ� 1�� ǥ��
			push(s, i, j);
			j--;
			printf("[%d, %d]�� �̵� \n", i, j);
			fprintf(fp, "[%d, %d]�� �̵� \n", i, j);
		}
		else if(maze[i-1][j-1] == 0) {
			maze[i-1][j-1] = 1;	//Ž���� ��δ� 1�� ǥ��
			push(s, i, j);
			i--;
			j--;
			printf("[%d, %d]�� �̵� \n", i, j);
			fprintf(fp, "[%d, %d]�� �̵� \n", i, j);
		}
		else {
			i = s->s_col[s->top];
			j = s->s_row[s->top];
			s->top--;
		}
		if(i == 11 && j == 15)	{//�ⱸ�� ã������  
			push(s, i, j);
			fclose(fp);
			break;
		}
	}
}
