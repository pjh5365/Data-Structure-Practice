#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 100

typedef struct tree {
	int data;
	struct tree *left;
	struct tree *right;
}Tree;

//큐를 선언// 
typedef Tree * Element;
Element data[MAX_QUEUE_SIZE]; // 요소의 배열
int front; // 전단
int rear; // 후단
//////////////////////

Tree * init_tree(Tree *root) {	//트리를 초기화 하는 함수 
	return NULL;
}

void is_empty_tree(Tree *root) {	//트리의 공백상태 확인함수 
	if(root == NULL)
		printf("트리가 공백상태입니다. \n");
}

void create_tree_left(Tree *root, int data) {	//노드를 연결시킬 루트와 데이터입력 
	Tree *left_node = (Tree *)malloc(sizeof(Tree));	//왼쪽노드 생성 
	
	root->left = left_node;	//루트와 새롭게 생성된 노드연결 
	
	left_node->data = data;	//왼쪽노드에 값입력 
	left_node->left = NULL;	//왼쪽노드의 링크를 NULL로 초기화 
	left_node->right = NULL;	//왼쪽노드의 링크를 NULL로 초기화 
} 

void create_tree_right(Tree *root, int data) {	//노드를 연결시킬 루트와 데이터입력 
	Tree *right_node = (Tree *)malloc(sizeof(Tree));	//왼쪽노드 생성 
	
	root->right = right_node;	//루트와 새롭게 생성된 노드연결
	
	right_node->data = data;	//오른쪽노드에 값입력 
	right_node->left = NULL;	//왼쪽노드의 링크를 NULL로 초기화 
	right_node->right = NULL;	//왼쪽노드의 링크를 NULL로 초기화 
} 

Tree * insert_node_first(Tree *root, int item) {	//루트가 없을때 루트를 만들어주는함수 
	Tree * new_node	= (Tree *)malloc(sizeof(Tree));
	new_node->data = item;
	new_node->left = new_node->right = NULL;
	
	return new_node;
}
/*
void insert_node(Tree *root, int item) {
	Tree *p = root;
	while(1) {
		if(item >= p->data) {
			if(p->right == NULL) {	//p의 오른쪽노드가 널이라면 그떄 삽입연산과 함께 break 
				create_tree_right(p, item);
				break;
			}
			else	//p의 오른쪽노드가 널이 아니면 한칸더 전진 
				p->right;	
		}
		else {
			if(p->left == NULL) {	//p의 왼쪽노드가 널이라면 그떄 삽입연산과 함께 break 
				create_tree_left(p, item);
				break;
			}
			else	//p의 왼쪽노드가 널이 아니면 한칸더 전진 
				p->left;	
		}
	}
}*/

void insert_node(Tree *root, int item) {	//노드를 추가하는 함수 
	if(item >= root->data) {
		if(root->right == NULL) 	//p의 오른쪽노드가 널이라면 그떄 삽입연산과 함께 break 
			create_tree_right(root, item);
		else	//p의 오른쪽노드가 널이 아니면 한칸더 전진 
			insert_node(root->right, item);	
	}
	else {
		if(root->left == NULL) 	//p의 왼쪽노드가 널이라면 그떄 삽입연산과 함께 break 
			create_tree_left(root, item);
		else	//p의 왼쪽노드가 널이 아니면 한칸더 전진 
			insert_node(root->left, item);		
	}
}

void search(Tree *root, int key) {
	if(root->left == NULL || root->right == NULL)	{//입력한 값을 찾을 수 없을때 
		printf("실패 : [%d] 찾을 수 없음! \n", key);
		return; 
	}
	if(root->data == key)
		printf("성공 [%d] \n", root->data);
	else if(root->data >= key)
		search(root->left, key);
	else if(root->data < key)
		search(root->right, key);
}

Tree * min_value(Tree *node) {	//최솟값을 찾는  함수 
	Tree *current = node;
	
	while(current->left)
		current = current->left;
		
	return current;
}

void max_value(Tree *root) {
	Tree *p;
	for(p = root; p != NULL; p= p->right)
	
	printf("트리의 최댓값 : [%d] \n", p->data);
	printf("트리의 최댓값은 이진탐색트리이기 때문에 가장 오른쪽노드에 있다.  \n");
}

Tree * delete_node(Tree *root, int key) {
	if(root == NULL)
		return root;
	
	if(key < root->data)
		root->left = delete_node(root->left, key);

	else if(key > root->data)
		root->right = delete_node(root->right, key);
		
	else
	{
		if(root->left == NULL)
		{
			Tree *tmp = root->right;
			free(root);
			return tmp;
		}
		else if(root->right == NULL)
		{
			Tree *tmp = root->left;
			free(root);
			return tmp;
		}
		
		Tree *tmp = min_value(root->right);	//후계자를 삭제할노드의 큰값의 최솟값으로 결정
		root->data = tmp->data;	//삭제할 값에 후계자를 덮어씌움 
		root->right = delete_node(root->right, tmp->data);	//후계자노드의 삭제 
	}
	return root;
}

/*
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
*/

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
		printf("[%d] ", root->data);
		inorder(root->right);
	}
}

void preorder(Tree *root) {
	if(root != NULL) {
		printf("[%d] ", root->data);
		preorder(root->left);
		preorder(root->right);
	}
}

void postorder(Tree *root) {
	if(root != NULL) {
		postorder(root->left);
		postorder(root->right);
		printf("[%d] ", root->data);
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
				printf("[%d] ", queue->data);
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
	int arr[10];
	int i, key;
	
	printf("[삽입연산] : ");
	for(i = 0; i < 10; i++)
		scanf("%d", &arr[i]);
	
	root = init_tree(root);
	
	root = insert_node_first(root, arr[0]);	//루트를 생성해야하므로 따로 호출 
	for(i = 1; i < 10; i++) {	//루트를 제외한 숫자 입력 
		insert_node(root, arr[i]);
	}

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
	
	for(i = 0; i < 2; i++) {
		printf("[탐색 연산] : ");
		scanf("%d",&key); 
		search(root, key);	
	}
	
	printf("original bintree : LevelOrder : ");
	levelorder(root);
	printf("\n");
	
	printf("case1: <3> 삭제 : LevelOrder : ");
	delete_node(root, 3);
	levelorder(root);
	printf("\n");
	
	printf("case2: <68> 삭제 : LevelOrder : ");
	delete_node(root, 68);
	levelorder(root);
	printf("\n");
	
	printf("case3: <18> 삭제 : LevelOrder : ");
	delete_node(root, 18);
	levelorder(root);
	printf("\n");
	
	printf("case4: <35> 삭제 : LevelOrder : ");
	delete_node(root, 35);
	levelorder(root);
	printf("\n");
	
	max_value(root); 
	
	return 0;
}
