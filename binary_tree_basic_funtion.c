#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 100

typedef struct tree {
	char data;
	struct tree *left;
	struct tree *right;
}Tree;

//ť�� ����// 
typedef Tree * Element;
Element data[MAX_QUEUE_SIZE]; // ����� �迭
int front; // ����
int rear; // �Ĵ�
//////////////////////

void init_tree(Tree *root) {	//Ʈ���� �ʱ�ȭ �ϴ� �Լ� 
	root = NULL;
}

void is_empty_tree(Tree *root) {	//Ʈ���� ������� Ȯ���Լ� 
	if(root == NULL)
		printf("Ʈ���� ��������Դϴ�. \n");
}

void create_tree_first(Tree **root, char root_d, char left_d, char right_d) {	//��Ʈ�ּҿ� ��Ʈ, ���ʰ�, ������ ���� �޾� Ʈ���� �����ϴ� �Լ�(���� ��带 ���� �����Ҷ�/ Ʈ���� ó�� �����Ҷ�)
		*root = (Tree *)malloc(sizeof(Tree));	//��Ʈ��带 ���� 
		Tree *left_node = (Tree *)malloc(sizeof(Tree));	//���ʳ����� 
		Tree *right_node = (Tree *)malloc(sizeof(Tree));	//�����ʳ����� 
		
		(*root)->data = root_d;	//��Ʈ�� ���Է� 
		(*root)->left = left_node;	//��Ʈ�� ���ʳ�� ���� 
		(*root)->right = right_node;	//��Ʈ�� �����ʳ�� ���� 
		
		left_node->data = left_d;	//���ʳ�忡 ���Է� 
		left_node->left = left_node->right = NULL;	//���ʳ���� ��ũ���� NULL�� �ʱ�ȭ 
		
		right_node->data = right_d;	//�����ʳ�忡 ���Է� 
		right_node->left = right_node->right = NULL;	//�����ʳ���� ��ũ���� NULL�� �ʱ�ȭ 
}

void create_tree_left(Tree *root, char data) {	//��带 �����ų ��Ʈ�� �������Է� 
	Tree *left_node = (Tree *)malloc(sizeof(Tree));	//���ʳ�� ���� 
	
	root->left = left_node;	//��Ʈ�� ���Ӱ� ������ ��忬�� 
	
	left_node->data = data;	//���ʳ�忡 ���Է� 
	left_node->left = NULL;	//���ʳ���� ��ũ�� NULL�� �ʱ�ȭ 
	left_node->right = NULL;	//���ʳ���� ��ũ�� NULL�� �ʱ�ȭ 
} 

void create_tree_right(Tree *root, char data) {	//��带 �����ų ��Ʈ�� �������Է� 
	Tree *right_node = (Tree *)malloc(sizeof(Tree));	//���ʳ�� ���� 
	
	root->right = right_node;	//��Ʈ�� ���Ӱ� ������ ��忬��
	
	right_node->data = data;	//�����ʳ�忡 ���Է� 
	right_node->left = NULL;	//���ʳ���� ��ũ�� NULL�� �ʱ�ȭ 
	right_node->right = NULL;	//���ʳ���� ��ũ�� NULL�� �ʱ�ȭ 
} 

char get_root(Tree *root) {	//��Ʈ�� ���� ��ȯ�ϴ��Լ� 
	return root->data;
}

//ť �Լ�����//
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
		error("  ť ��ȭ ����");
	rear = (rear + 1) % MAX_QUEUE_SIZE;
	data[rear] = val;
}

Element dequeue()
{
	if (is_empty())
		error("  ť ���� ����");
	front = (front + 1) % MAX_QUEUE_SIZE;
	return data[front];
}

Element peek()
	{
	if (is_empty())
		error("  ť ���� ����");
	return data[(front + 1) % MAX_QUEUE_SIZE];
}
//ť �Լ� ��// 

//��ȸ�Լ�����// 
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
	Element queue;	//ť�� ��ҵ��� ���� �������� 
	if(root != NULL) {
		init_queue();	//ť�ʱ�ȭ 
		enqueue(root);	//ť�� root�� �����Ҵ�� root�� �ּҸ� �Ѱ��� 
		while(!is_empty()){	//ť�� ����������ʴٸ� ���� 
			queue = dequeue();	//��Ҹ� ���� ������ ť�� ��Ҹ� �����Ѱ��� 
			if(queue != NULL) {	//������ NULL�� �ƴҶ����� 
				printf("[%c] ", queue->data);
				enqueue(queue->left);
				enqueue(queue->right);
			}
		}
	}
}

//��ȸ�Լ���// 

int get_count(Tree *root) {		//Ʈ���� ������ ��ȯ�ϴ� �Լ� 
	if(root != NULL)
		return 1 + get_count(root->left) + get_count(root->right);	//������ ������ ��ȯ�ϸ� 1���߰��� 
}

void get_leaf_count(Tree *root, int *leaf_count) {	//�ܸ������ ������ ��ȯ�ϴ� �Լ�
	if(root != NULL) {
		if(root->left == NULL && root->right == NULL)
			(*leaf_count)++;
		get_leaf_count(root->left, leaf_count);	//�̹� �ּҰ��� ������ ������ &�� �ѱ��ʿ���� 
		get_leaf_count(root->right, leaf_count);	//�̹� �ּҰ��� ������ ������ &�� �ѱ��ʿ���� 
	}
}

int get_height(Tree *root) {	//Ʈ���� ����(����)�� ��ȯ�ϴ� �Լ�  (���� �򰥸��ºκ�/����������)
	int lh, rh;	//����Ʈ���� ������Ʈ���� ���̸� �ľ��� ���� 
	if(root == NULL) 
		return 0;
	lh = get_height(root->left);
	rh = get_height(root->right);
	return (lh > rh) ? lh+1 : rh+1;	//�� ū���� ��ȯ�ϱ����� ���׿����ڻ�� 
}

int main(void) {
	Tree *root;
	int leaf_count;
	init_tree(root);
	create_tree_first(&root, 'A', 'B', 'C');	//ó�� �����ϱ����� root�� �ּҰ��� �Ѱ��־ �����Ҵ��� �޵����� 
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
	
	printf("����� ���� : %d \n", get_count(root));
	get_leaf_count(root, &leaf_count);
	printf("�ܸ������ ��: %d \n", leaf_count);
	printf("Ʈ���� ����: %d\n", get_height(root));
	
	
	return 0;
}
