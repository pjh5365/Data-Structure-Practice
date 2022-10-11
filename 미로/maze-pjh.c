#include <stdio.h>
#include <stdlib.h>

typedef struct stack {
	int s_col[65];	//0의 갯수만큼선언 
	int s_row[65];
	int top;
}Stack;

void load_data(int *col, int *row, int maze[][20]);	//미로를 불러오는 함수 
void mazeFind(Stack *s, int col, int row, int maze[][20]);
void push(Stack *s, int i, int j);

int main(void) {
	Stack s;
	s.top = -1;	//스택초기화
	
	FILE *fp = fopen("maze-pjh.out", "a");	//함수에서 사용했으므로 w로 부르면 파일이 날라감 
	if(fp == NULL) {
		printf("파일오픈에러 \n");
		return -1;
	}
	
	int col;
	int row;
	int maze[15][20];
	int i, j;
	
	load_data(&col, &row, maze);
	
	printf("경계를 포함한 미로의 크기 \n");
	printf("행 : %d 열 : %d \n", col, row);
	printf("미로출력 (1은 벽 0 은 길 입구는maze[1][1], 출구는 maze[11][15]) \n\n") ;
	for(i = 0; i < col; i++) {
		for(j = 0; j < row; j++) {
			printf("%d ", maze[i][j]);
		}
		printf("\n");
	}
	
	mazeFind(&s, col, row, maze);
	printf("\n\n최소경로 출력\n\n");
	fprintf(fp, "\n\n최소경로 출력\n\n"); 
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
	
	int i = 0, j = 0;	//미로를 담기위해 선언
	int input;
	
	if(fp == NULL) {
		printf("파일오픈에러 \n");
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
		printf("파일오픈에러 \n");
		return -1;
	}
	
	int i = 1, j = 1;
	printf("\n\n\n미로 찾기 시작\n\n\n");
	fprintf(fp, "미로 찾기 시작\n\n\n");
	printf("[1, 1]에서 시작 \n");
	fprintf(fp, "[1, 1]에서 시작 \n");
	
	while(1)  {
		if(maze[i-1][j] == 0) {
			maze[i-1][j] = 1;	//탐색한 경로는 1로 표시 
			push(s, i, j);
			i--;
			printf("[%d, %d]로 이동 \n", i, j);
			fprintf(fp, "[%d, %d]로 이동 \n", i, j);
		}
		else if(maze[i-1][j+1] == 0) {
			maze[i-1][j+1] = 1;	//탐색한 경로는 1로 표시
			push(s, i, j);
			i--;
			j++;
			printf("[%d, %d]로 이동 \n", i, j);
			fprintf(fp, "[%d, %d]로 이동 \n", i, j);
		}
		else if(maze[i][j+1] == 0) {
			maze[i][j+1] = 1;	//탐색한 경로는 1로 표시
			push(s, i, j);
			j++;
			printf("[%d, %d]로 이동 \n", i, j);
			fprintf(fp, "[%d, %d]로 이동 \n", i, j);
		}
		else if(maze[i+1][j+1] == 0) {
			maze[i+1][j+1] = 1;	//탐색한 경로는 1로 표시
			push(s, i, j);
			i++;
			j++;
			printf("[%d, %d]로 이동 \n", i, j);
			fprintf(fp, "[%d, %d]로 이동 \n", i, j);
		}
		else if(maze[i+1][j] == 0) {
			maze[i+1][j] = 1;	//탐색한 경로는 1로 표시
			push(s, i, j);
			i++;
			printf("[%d, %d]로 이동 \n", i, j);
			fprintf(fp, "[%d, %d]로 이동 \n", i, j);
		}
		else if(maze[i+1][j-1] == 0) {
			maze[i+1][j-1] = 1;	//탐색한 경로는 1로 표시
			push(s, i, j);
			i++;
			j--;
			printf("[%d, %d]로 이동 \n", i, j);
			fprintf(fp, "[%d, %d]로 이동 \n", i, j);
		}
		else if(maze[i][j-1] == 0) {
			maze[i][j-1] = 1;	//탐색한 경로는 1로 표시
			push(s, i, j);
			j--;
			printf("[%d, %d]로 이동 \n", i, j);
			fprintf(fp, "[%d, %d]로 이동 \n", i, j);
		}
		else if(maze[i-1][j-1] == 0) {
			maze[i-1][j-1] = 1;	//탐색한 경로는 1로 표시
			push(s, i, j);
			i--;
			j--;
			printf("[%d, %d]로 이동 \n", i, j);
			fprintf(fp, "[%d, %d]로 이동 \n", i, j);
		}
		else {
			i = s->s_col[s->top];
			j = s->s_row[s->top];
			s->top--;
		}
		if(i == 11 && j == 15)	{//출구를 찾았을때  
			push(s, i, j);
			fclose(fp);
			break;
		}
	}
}
