#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 100;

typedef int element;
typedef struct TreeNode {
	element key;
	struct TreeNode* left, * right;
}TreeNode;

TreeNode* search(TreeNode* node, int key) {
	if (node == NULL) return NULL;
	if (key == node->key) {
		printf("%d =>", node->key);
		return node;
	}
	else if (key < node->key) {
		printf("%d =>", node->key);
		return search(node->left, key);
	}
	else {	
		printf("%d =>", node->key);
		return search(node->right, key);

	}

}

TreeNode* newNode(int key)
{
	TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
	temp->key = key;
	temp->left = temp->right = NULL;
	return temp;
}

TreeNode* insertNode(TreeNode* node, int key) {
	if (node == NULL) return newNode(key);
	if (key < node->key)
		node->left = insertNode(node->left, key);
	else if (key > node->key)
		node->right = insertNode(node->right, key);

	return node;
}

TreeNode* minValueNode(TreeNode* node)
{
	TreeNode* current = node;
	while (current->left != NULL)
		current = current->left;
	return current;
}

TreeNode* deleteNode(TreeNode* root, int key)
{
	if (root == NULL) return root;

	if (key < root->key)
		root->left = deleteNode(root->left, key);
	else if (key > root->key)
		root->right = deleteNode(root->right, key);
	else {
		if (root->left == NULL) {
			TreeNode* temp = root->right;
			free(root);
			return temp;
		}
		else if (root->right == NULL) {
			TreeNode* temp = root->left;
			free(root);
			return temp;
		}
		TreeNode* temp = minValueNode(root->right);
		root->key = temp->key;
		root->right = deleteNode(root->right, temp->key);
	}
	return root;
}

void inorder(TreeNode* root) {
	if (root) {
		inorder(root->left);
		printf("%d ", root->key);
		inorder(root->right);
	}
}
int main() {
	int n,ser;
	int seed;
	TreeNode* root = NULL;
	TreeNode* tmp = NULL;
	printf("random number generation(1~%d)\n", 500);
	printf("the number of nodes in BST(less than and equal to 50) : ");
	scanf("%d", & n);
	printf("seed : ");
	scanf("%d", &seed);
	printf("\ncreating a BST from random numbers\n");
	srand(seed);
	printf("generating number : ");
	for (int i = 0; i < n; i++) {
		int random = rand()% 500;
		root = insertNode(root, random);
		printf("%d ", random);
	}
	printf("\nthe key to search : ");
	scanf("%d", &ser);
	printf("the search process : ");
	if (search(root, ser) != NULL) {
		printf("\nthe element is in BST\n\n");
	}
	else {
		printf("\nthe element isn't in BST\n\n");
	}
	printf("inorder traversal of the BST shows the sorted sequence\n");
	inorder(root);
}
