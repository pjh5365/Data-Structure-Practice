#include <stdio.h>

void bouble_sort(int a[]) {
	int t, i, j;

	for(i = 9; i > 0; i--) {	//0 ~ i-1���� 
		for(j = 0; j < i; j++) {	//���������� ���ʿ䰡 �����Ƿ� 
			if(a[j] > a[j+1]) {
				t = a[j];
				a[j] = a[j+1];
				a[j+1] = t;
			}
		}
	}
}

int main(void) {
	
	int a[10] = {10, 22, 43, 5, 4, 7, 8, 72, 15, 1};
	int i;
	
	bouble_sort(a);
	
	for(i = 0; i < 10; i++) {
		printf("[%d] ", a[i]);
	}
}
