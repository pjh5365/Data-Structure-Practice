#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 100
#define MAX(a,b) ((a>b) ? a:b)

typedef struct tree {
	int data;
	struct tree *left;
	struct tree *right;
}Tree;

//ť�� ����// 
typedef Tree * Element;
Element data[MAX_QUEUE_SIZE]; // ����� �迭
int front; // ����
int rear; // �Ĵ�
//////////////////////

Tree * init_tree(Tree *root) {	//Ʈ���� �ʱ�ȭ �ϴ� �Լ� 
	return NULL;
}

void is_empty_tree(Tree *root) {	//Ʈ���� ������� Ȯ���Լ� 
	if(root == NULL)
		printf("Ʈ���� ��������Դϴ�. \n");
}

void create_tree_left(Tree *root, int data) {	//��带 �����ų ��Ʈ�� �������Է� 
	Tree *left_node = (Tree *)malloc(sizeof(Tree));	//���ʳ�� ���� 
	
	root->left = left_node;	//��Ʈ�� ���Ӱ� ������ ��忬�� 
	
	left_node->data = data;	//���ʳ�忡 ���Է� 
	left_node->left = NULL;	//���ʳ���� ��ũ�� NULL�� �ʱ�ȭ 
	left_node->right = NULL;	//���ʳ���� ��ũ�� NULL�� �ʱ�ȭ 
} 

void create_tree_right(Tree *root, int data) {	//��带 �����ų ��Ʈ�� �������Է� 
	Tree *right_node = (Tree *)malloc(sizeof(Tree));	//���ʳ�� ���� 
	
	root->right = right_node;	//��Ʈ�� ���Ӱ� ������ ��忬��
	
	right_node->data = data;	//�����ʳ�忡 ���Է� 
	right_node->left = NULL;	//���ʳ���� ��ũ�� NULL�� �ʱ�ȭ 
	right_node->right = NULL;	//���ʳ���� ��ũ�� NULL�� �ʱ�ȭ 
} 

Tree * insert_node_first(Tree *root, int item) {	//��Ʈ�� ������ ��Ʈ�� ������ִ��Լ� 
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
			if(p->right == NULL) {	//p�� �����ʳ�尡 ���̶�� �׋� ���Կ���� �Բ� break 
				create_tree_right(p, item);
				break;
			}
			else	//p�� �����ʳ�尡 ���� �ƴϸ� ��ĭ�� ���� 
				p->right;	
		}
		else {
			if(p->left == NULL) {	//p�� ���ʳ�尡 ���̶�� �׋� ���Կ���� �Բ� break 
				create_tree_left(p, item);
				break;
			}
			else	//p�� ���ʳ�尡 ���� �ƴϸ� ��ĭ�� ���� 
				p->left;	
		}
	}
}*/

void insert_node(Tree *root, int item) {	//��带 �߰��ϴ� �Լ� 
	if(item >= root->data) {
		if(root->right == NULL) 	//p�� �����ʳ�尡 ���̶�� �׋� ���Կ���
			create_tree_right(root, item);
		else	//p�� �����ʳ�尡 ���� �ƴϸ� ��ĭ�� ���� 
			insert_node(root->right, item);	
	}
	else {
		if(root->left == NULL) 	//p�� ���ʳ�尡 ���̶�� �׋� ���Կ���
			create_tree_left(root, item);
		else	//p�� ���ʳ�尡 ���� �ƴϸ� ��ĭ�� ���� 
			insert_node(root->left, item);		
	}
}

int get_height(Tree *root) {	//Ʈ���� ����(����)�� ��ȯ�ϴ� �Լ�  (���� �򰥸��ºκ�/����������)
	int height = 0;
	if(root != NULL)
		height = MAX(get_height(root->left), get_height(root->right)) +1;
	return height;
}

Tree * rotate_LL(Tree *root) {	//LLȸ�� 
	Tree * tmp = root->left;
	root->left = tmp->right;
	tmp->right = root;
	
	return tmp;
}

Tree * rotate_RR(Tree *root) {	//RRȸ�� 
	Tree * tmp = root->right;
	root->right = tmp->left;
	tmp->left = root;
	
	return tmp;
}

Tree * rotate_RL(Tree *root) {	//RLȸ�� 
	Tree * tmp = root->right;
	root->right = rotate_LL(tmp);
	return rotate_RR(root);	
}

Tree * rotate_LR(Tree *root) {	//LRȸ�� 
	Tree * tmp = root->left;
	root->left = rotate_RR(tmp);
	return rotate_LL(root);		
}

int get_balance(Tree *root) { //�����μ��� ���ϴ� �Լ� 
	if (root == NULL) return 0;
	return get_height(root->left) - get_height(root->right); //���� ����Ʈ�� ���� - ������ ����Ʈ�� ���� 
}

Tree * balance_tree(Tree **root) { //Ʈ���� ���� ����
	int height = get_balance(*root); //���� ����-������ ����
	if (height > 1) { //������ �� ũ�ٸ� ���� ����Ʈ�� ������ ����
		if (get_balance((*root)->left) > 0) //���� ��尡 �� ũ��
			*root = rotate_LL(*root); 
		
		else 
			*root = rotate_LR(*root); 
		
	}
	else if (height < -1) { //������ ����Ʈ�� ������ ����
		if (get_balance((*root)->right) < 0)  //������ ��尡 �� ũ��
			*root = rotate_RR(*root); 
		
		else 
			*root = rotate_RL(*root); 
		
	}
	//0�̸� ������ �´� ���̹Ƿ� �н�
		return *root;
}

Tree * insert_node_AVL(Tree **root, int item) {
	if (*root == NULL) {
		*root = (Tree *)malloc(sizeof(Tree));
		(*root)->data = item;
		(*root)->left = NULL;
		(*root)->right = NULL;
	}
	else if (item < (*root)->data) {
		(*root)->left = insert_node_AVL(&((*root)->left), item);
		*root = balance_tree(root);
	}
	else if (item >(*root)->data) {
		(*root)->right = insert_node_AVL(&((*root)->right), item);
		*root = balance_tree(root);
	}
	else {
		printf("\n �̹� ���� Ű�� �ֽ��ϴ�! \n");
		exit(1);
	}
	return *root;
}

void search(Tree *root, int key) {
	if(root->left == NULL || root->right == NULL)	{//�Է��� ���� ã�� �� ������ 
		printf("���� : [%d] ã�� �� ����! \n", key);
		return; 
	}
	if(root->data == key)
		printf("���� [%d] \n", root->data);
	else if(root->data >= key)
		search(root->left, key);
	else if(root->data < key)
		search(root->right, key);
}

Tree * min_value(Tree *node) {	//�ּڰ��� ã��  �Լ� 
	Tree *current = node;
	
	while(current->left)
		current = current->left;
		
	return current;
}

void max_value(Tree *root) {
	Tree *p;
	for(p = root; p != NULL; p= p->right)
	
	printf("Ʈ���� �ִ� : [%d] \n", p->data);
	printf("Ʈ���� �ִ��� ����Ž��Ʈ���̱� ������ ���� �����ʳ�忡 �ִ�.  \n");
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
		
		Tree *tmp = min_value(root->right);	//�İ��ڸ� �����ҳ���� ū���� �ּڰ����� ����
		root->data = tmp->data;	//������ ���� �İ��ڸ� ����� 
		root->right = delete_node(root->right, tmp->data);	//�İ��ڳ���� ���� 
	}
	return root;
}

/*
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
*/

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
	Element queue;	//ť�� ��ҵ��� ���� �������� 
	if(root != NULL) {
		init_queue();	//ť�ʱ�ȭ 
		enqueue(root);	//ť�� root�� �����Ҵ�� root�� �ּҸ� �Ѱ��� 
		while(!is_empty()){	//ť�� ����������ʴٸ� ���� 
			queue = dequeue();	//��Ҹ� ���� ������ ť�� ��Ҹ� �����Ѱ��� 
			if(queue != NULL) {	//������ NULL�� �ƴҶ����� 
				printf("[%d] ", queue->data);
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

int main(void) {
	Tree *root;
	int leaf_count;
	int key;
	
	root = init_tree(root);
	
	root = insert_node_AVL(&root, 30);	//��Ʈ�� �����ؾ��ϹǷ� ����ȣ��
	printf("\nAVL(30) :");
	levelorder(root);
	
	insert_node_AVL(&root, 40);
	printf("\nAVL(40) :");
	levelorder(root);

	insert_node_AVL(&root, 100);
	printf("\nAVL(100) :");
	levelorder(root);
	
	insert_node_AVL(&root, 20);
	printf("\nAVL(20) :");
	levelorder(root);
	
	insert_node_AVL(&root, 10);
	printf("\nAVL(10) :");
	levelorder(root);
	
	insert_node_AVL(&root, 60);
	printf("\nAVL(60) :");
	levelorder(root);
	
	insert_node_AVL(&root, 70);
	printf("\nAVL(70) :");
	levelorder(root);
	
	insert_node_AVL(&root, 120);
	printf("\nAVL(120) :");
	levelorder(root);
	
	insert_node_AVL(&root, 110);
	printf("\nAVL(110) :");
	levelorder(root);
	
	printf("\n����� ���� : %d \n", get_count(root));
	get_leaf_count(root, &leaf_count);
	printf("�ܸ������ ��: %d \n", leaf_count);
	printf("Ʈ���� ����: %d\n", get_height(root));
	
	return 0;
}
