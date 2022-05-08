#include <stdio.h>
#include <stdlib.h>

typedef struct binary_tree{
	int data;	//데이터를 담을 공간 
	struct binary_tree *left;	//왼쪽노드를 가르킬 포인터 
	struct binary_tree *rigth;	//오른쪽 노드를 가르킬 포인터 
}Tree;

void init(Tree *root) {	//트리를 초기화하는 함수 
	root->left = root->rigth = NULL;
}

void is_empty(Tree *root) {
	if(root->left == NULL && root->rigth == NULL) 
		printf("Tree is empty \n");
	else
		printf("Tree is not empty \n");
}

void create_tree(Tree *root,int root_d, int left_d, int rigth_d) {	//루트와 왼쪽노드에 들어갈 값, 오른쪽 노드에 들어갈 값을 받아 트리를 생성 
	Tree *left_t = (Tree *)malloc(sizeof(Tree));	//왼쪽 노드를 동적할당 
	Tree *rigth_t = (Tree *)malloc(sizeof(Tree));	//오른쪽 노드를 동적할당 
	root->data = root_d;
	left_t->data = left_d;
	rigth_t->data = rigth_d;
	root->left = left_t;	//루트와 왼쪽노드 연결 
	root->rigth = rigth_t;	//루트와 오른쪽노드 연결 
	left_t->left = left_t->rigth = rigth_t->left = rigth_t->rigth = NULL;	//단말노드의 링크값을 널값으로 초기화 
	left_t->left = left_t->rigth = NULL;	//단말노드의 링크값을 널값으로 초기화 
} 

void inorder(Tree *root) {	//중위순회 
	if(root != NULL) {
		inorder(root->left);
		printf("[%d]-> ", root->data);
		inorder(root->rigth);
	}
}

int get_root(Tree *root) {	//트리의 값을 반환 
	return root->data;
}

int get_count(Tree *root) {		//트리의 노드수를 반환하는 함수 
	if(root != NULL)
		return 1 + get_count(root->left) + get_count(root->rigth);	//나머지 노드들을 순환하며 1씩추가함 
}

void get_leaf_count(Tree *root, int *leaf_count) {	//단말노드이 갯수를 반환하는 함수
	if(root != NULL) {
		if(root->left == NULL && root->rigth == NULL)
			(*leaf_count)++;
		get_leaf_count(root->left, leaf_count);	//이미 주소값을 가지기 때문에 &로 넘길필요없음 
		get_leaf_count(root->rigth, leaf_count);	//이미 주소값을 가지기 때문에 &로 넘길필요없음 
	}
}

int get_height(Tree *root) {	//트리의 높이(레벨)를 반환하는 함수  (가장 헷갈리는부분/예제참고함)
	int lh, rh;	//왼쪽트리와 오른쪽트리의 높이를 파악할 변수 
	if(root == NULL) 
		return 0;
	lh = get_height(root->left);
	rh = get_height(root->rigth);
	return (lh > rh) ? lh+1 : rh+1;	//더 큰값을 반환하기위해 삼항연산자사용 
}

int main(void) {

	Tree *root = (Tree *)malloc(sizeof(Tree));
	int leaf_count = 0;
	init(root);	
	
	is_empty(root);
	create_tree(root, 10, 20, 30);
	is_empty(root);
	inorder(root);
	printf("\n\n");
	create_tree(root->left, 40, 50, 60);
	create_tree(root->rigth, 40, 50, 60);
	inorder(root);
	printf("\n\n");
	
	printf("루트의 값: %d \n", get_root(root));
	printf("노드의 수: %d \n", get_count(root));
	get_leaf_count(root, &leaf_count);
	printf("단말노드의 수: %d \n", leaf_count);
	printf("트리의 높이: %d\n", get_height(root));
	
	free(root); 
	
	return 0;
}
