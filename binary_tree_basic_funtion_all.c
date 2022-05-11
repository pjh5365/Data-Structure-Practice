#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 100

typedef struct tree {
	char data;
	struct tree *left;
	struct tree *right;
}Tree;

//큐를 선언// 
typedef Tree * Element;
Element data[MAX_QUEUE_SIZE]; // 요소의 배열
int front; // 전단
int rear; // 후단
//////////////////////

void init_tree(Tree *root) {	//트리를 초기화 하는 함수 
	root = NULL;
}

void is_empty_tree(Tree *root) {	//트리의 공백상태 확인함수 
	if(root == NULL)
		printf("트리가 공백상태입니다. \n");
}

void create_tree_first(Tree **root, char root_d, char left_d, char right_d) {	//루트주소와 루트, 왼쪽값, 오른쪽 값을 받아 트리를 생성하는 함수(양쪽 노드를 전부 생성할때/ 트리를 처음 생성할때)
		*root = (Tree *)malloc(sizeof(Tree));	//루트노드를 생성 
		Tree *left_node = (Tree *)malloc(sizeof(Tree));	//왼쪽노드생성 
		Tree *right_node = (Tree *)malloc(sizeof(Tree));	//오른쪽노드생성 
		
		(*root)->data = root_d;	//루트에 값입력 
		(*root)->left = left_node;	//루트와 왼쪽노드 연결 
		(*root)->right = right_node;	//루트와 오른쪽노드 연결 
		
		left_node->data = left_d;	//왼쪽노드에 값입력 
		left_node->left = left_node->right = NULL;	//왼쪽노드의 링크들을 NULL로 초기화 
		
		right_node->data = right_d;	//오른쪽노드에 값입력 
		right_node->left = right_node->right = NULL;	//오른쪽노드의 링크들을 NULL로 초기화 
}

void create_tree_left(Tree *root, char data) {	//노드를 연결시킬 루트와 데이터입력 
	Tree *left_node = (Tree *)malloc(sizeof(Tree));	//왼쪽노드 생성 
	
	root->left = left_node;	//루트와 새롭게 생성된 노드연결 
	
	left_node->data = data;	//왼쪽노드에 값입력 
	left_node->left = NULL;	//왼쪽노드의 링크를 NULL로 초기화 
	left_node->right = NULL;	//왼쪽노드의 링크를 NULL로 초기화 
} 

void create_tree_right(Tree *root, char data) {	//노드를 연결시킬 루트와 데이터입력 
	Tree *right_node = (Tree *)malloc(sizeof(Tree));	//왼쪽노드 생성 
	
	root->right = right_node;	//루트와 새롭게 생성된 노드연결
	
	right_node->data = data;	//오른쪽노드에 값입력 
	right_node->left = NULL;	//왼쪽노드의 링크를 NULL로 초기화 
	right_node->right = NULL;	//왼쪽노드의 링크를 NULL로 초기화 
} 

char get_root(Tree *root) {	//루트의 값을 반환하는함수 
	return root->data;
}

//큐 함수시작//
void error(char str[])
{
	printf("%s\n", str);
	exit(1);
}

void init_queue() { front = rear = 0; }
int is_empty() { return front == rear; }
int is_full() { return front == (rear + 1) % MAX_QUEUE_SIZE; }
int size() { return(rear - front + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE; }

void enqueue(Element val)
{
	if (is_full())
		error("  큐 포화 에러");
	rear = (rear + 1) % MAX_QUEUE_SIZE;
	data[rear] = val;
}

Element dequeue()
{
	if (is_empty())
		error("  큐 공백 에러");
	front = (front + 1) % MAX_QUEUE_SIZE;
	return data[front];
}

Element peek()
	{
	if (is_empty())
		error("  큐 공백 에러");
	return data[(front + 1) % MAX_QUEUE_SIZE];
}
//큐 함수 끝// 

//순회함수시작// 
void inorder(Tree *root) {
	if(root != NULL) {
		inorder(root->left);
		printf("[%c] ", root->data);
		inorder(root->right);
	}
}

void preorder(Tree *root) {
	if(root != NULL) {
		printf("[%c] ", root->data);
		preorder(root->left);
		preorder(root->right);
	}
}

void postorder(Tree *root) {
	if(root != NULL) {
		postorder(root->left);
		postorder(root->right);
		printf("[%c] ", root->data);
	}
}

void levelorder(Tree *root) {
	Element queue;	//큐의 요소들을 받을 변수선언 
	if(root != NULL) {
		init_queue();	//큐초기화 
		enqueue(root);	//큐에 root즉 동적할당된 root의 주소를 넘겨줌 
		while(!is_empty()){	//큐가 비워져있지않다면 실행 
			queue = dequeue();	//요소를 받을 변수에 큐의 요소를 빼서넘겨줌 
			if(queue != NULL) {	//변수가 NULL이 아닐때실행 
				printf("[%c] ", queue->data);
				enqueue(queue->left);
				enqueue(queue->right);
			}
		}
	}
}

//순회함수끝// 

int get_count(Tree *root) {		//트리의 노드수를 반환하는 함수 
	if(root != NULL)
		return 1 + get_count(root->left) + get_count(root->right);	//나머지 노드들을 순환하며 1씩추가함 
}

void get_leaf_count(Tree *root, int *leaf_count) {	//단말노드이 갯수를 반환하는 함수
	if(root != NULL) {
		if(root->left == NULL && root->right == NULL)
			(*leaf_count)++;
		get_leaf_count(root->left, leaf_count);	//이미 주소값을 가지기 때문에 &로 넘길필요없음 
		get_leaf_count(root->right, leaf_count);	//이미 주소값을 가지기 때문에 &로 넘길필요없음 
	}
}

int get_height(Tree *root) {	//트리의 높이(레벨)를 반환하는 함수  (가장 헷갈리는부분/예제참고함)
	int lh, rh;	//왼쪽트리와 오른쪽트리의 높이를 파악할 변수 
	if(root == NULL) 
		return 0;
	lh = get_height(root->left);
	rh = get_height(root->right);
	return (lh > rh) ? lh+1 : rh+1;	//더 큰값을 반환하기위해 삼항연산자사용 
}

int main(void) {
	Tree *root;
	int leaf_count;
	init_tree(root);
	create_tree_first(&root, 'A', 'B', 'C');	//처음 생성하기위해 root의 주소값을 넘겨주어서 동적할당을 받도록함 
	create_tree_left(root->left, 'D');
	create_tree_right(root->left, 'E');
	create_tree_left(root->right, 'F');

	printf("In-Order : ");
	inorder(root);
	printf("\n");
	
	printf("Pre-Order : ");
	preorder(root);
	printf("\n");
	
	printf("Post-Order : ");
	postorder(root);
	printf("\n");
	
	printf("Level-Order : ");
	levelorder(root);
	printf("\n");
	
	printf("노드의 갯수 : %d \n", get_count(root));
	get_leaf_count(root, &leaf_count);
	printf("단말노드의 수: %d \n", leaf_count);
	printf("트리의 높이: %d\n", get_height(root));
	
	
	return 0;
}
