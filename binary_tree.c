#include <stdio.h>
#include <stdlib.h>

typedef struct binary_tree{
	int data;	//�����͸� ���� ���� 
	struct binary_tree *left;	//���ʳ�带 ����ų ������ 
	struct binary_tree *rigth;	//������ ��带 ����ų ������ 
}Tree;

void init(Tree *root) {	//Ʈ���� �ʱ�ȭ�ϴ� �Լ� 
	root->left = root->rigth = NULL;
}

void is_empty(Tree *root) {
	if(root->left == NULL && root->rigth == NULL) 
		printf("Tree is empty \n");
	else
		printf("Tree is not empty \n");
}

void create_tree(Tree *root,int root_d, int left_d, int rigth_d) {	//��Ʈ�� ���ʳ�忡 �� ��, ������ ��忡 �� ���� �޾� Ʈ���� ���� 
	Tree *left_t = (Tree *)malloc(sizeof(Tree));	//���� ��带 �����Ҵ� 
	Tree *rigth_t = (Tree *)malloc(sizeof(Tree));	//������ ��带 �����Ҵ� 
	root->data = root_d;
	left_t->data = left_d;
	rigth_t->data = rigth_d;
	root->left = left_t;	//��Ʈ�� ���ʳ�� ���� 
	root->rigth = rigth_t;	//��Ʈ�� �����ʳ�� ���� 
	left_t->left = left_t->rigth = rigth_t->left = rigth_t->rigth = NULL;	//�ܸ������ ��ũ���� �ΰ����� �ʱ�ȭ 
	left_t->left = left_t->rigth = NULL;	//�ܸ������ ��ũ���� �ΰ����� �ʱ�ȭ 
} 

void inorder(Tree *root) {	//������ȸ 
	if(root != NULL) {
		inorder(root->left);
		printf("[%d]-> ", root->data);
		inorder(root->rigth);
	}
}

int get_root(Tree *root) {	//Ʈ���� ���� ��ȯ 
	return root->data;
}

int get_count(Tree *root) {		//Ʈ���� ������ ��ȯ�ϴ� �Լ� 
	if(root != NULL)
		return 1 + get_count(root->left) + get_count(root->rigth);	//������ ������ ��ȯ�ϸ� 1���߰��� 
}

void get_leaf_count(Tree *root, int *leaf_count) {	//�ܸ������ ������ ��ȯ�ϴ� �Լ�
	if(root != NULL) {
		if(root->left == NULL && root->rigth == NULL)
			(*leaf_count)++;
		get_leaf_count(root->left, leaf_count);	//�̹� �ּҰ��� ������ ������ &�� �ѱ��ʿ���� 
		get_leaf_count(root->rigth, leaf_count);	//�̹� �ּҰ��� ������ ������ &�� �ѱ��ʿ���� 
	}
}

int get_height(Tree *root) {	//Ʈ���� ����(����)�� ��ȯ�ϴ� �Լ�  (���� �򰥸��ºκ�/����������)
	int lh, rh;	//����Ʈ���� ������Ʈ���� ���̸� �ľ��� ���� 
	if(root == NULL) 
		return 0;
	lh = get_height(root->left);
	rh = get_height(root->rigth);
	return (lh > rh) ? lh+1 : rh+1;	//�� ū���� ��ȯ�ϱ����� ���׿����ڻ�� 
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
	
	printf("��Ʈ�� ��: %d \n", get_root(root));
	printf("����� ��: %d \n", get_count(root));
	get_leaf_count(root, &leaf_count);
	printf("�ܸ������ ��: %d \n", leaf_count);
	printf("Ʈ���� ����: %d\n", get_height(root));
	
	free(root); 
	
	return 0;
}
