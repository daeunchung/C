#include <stdio.h>
#include <Windows.h>
struct Node {
	int key;
	Node * left;
	Node * right;
};
struct Tree {
	int count;
	Node * root;
};
Tree * CreateTree(Tree * tree);
void AddKey(Tree * tree, int key);
void PrintTree(Tree * tree);
void PrintNode(Node *node);
int FindKey(Tree * tree, int key);
void DeleteKey(Tree * tree, int key);
int KeyCheck(Tree* tree, int key);

Tree * CreateTree(Tree * tree) {
	Tree * tree = new Tree();
	memset(tree, 0, sizeof(Tree));
	return tree;
}
void AddKey(Tree * tree, int key) {
	Node* node = new Node();
	node->key = key;
	node->left = 0;
	node->right = 0;
	if (tree->root == 0) {	// ��� 0�� ������ root�� �߰����ְ�
		tree->root = node;
		return;	// return���� �������� , �ؿ� ���� X
	}

	// ������ʹ� ��� 0�� �ƴϾ����� ����
	Node* cur = tree->root;
	while (1) {
		if (cur->key == key) {
			printf("�ߺ�Ű\n");
			return;
		}
		if (cur->key > key) {
			if (cur->left == 0) {
				cur->left = node;
				return;
			}
			cur = cur->left;
		}
		if (cur->key > key) {
			if (cur->right == 0) {
				cur->right = node;
				return;
			}
			cur = cur->right;
		}
	}
}
void PrintTree(Tree * tree) {
	PrintNode(tree->root);
}
void PrintNode(Node *node) {	// L Root R in-order traversal �ΰ��� ���� ��ȸ
	if (node == 0) return;
	PrintNode(node->left);
	printf("��� : %d\n", node->key);
	PrintNode(node->right);
}
int FindKey(Tree * tree, int key) {
	int result = -1;
	Node* cur = tree->root;
	while (1) {
		if (cur->key == key) {
			result = 1;
			return result;
		}
		if (cur->key > key) {
			if (cur->left == 0)
				return result;
			cur = cur->left;
		}
		else {
			if (cur->right == 0)
				return result;
			cur = cur->right;
		}
	}
}

void DeleteKey(Tree * tree, int key) {
	if (KeyCheck(tree, key) == -1) {
		printf("���� ���� �����ϴ� %d\n", key); return;
	} // ���� Ű�� �� ��� ������

	// �ִ� Ű�̸� �Ʒ��� ����
	Node * par = 0;	// cur�� ��� �̵���Ű�� �̵��� cur�� �θ� �������� Ʈ��ŷ���ִ� par(parent)
	Node* cur = tree->root;
	while (cur->key != key) {
		if (cur->key < key) {
			par = cur; // cur �̵����� �θ� ǥ���صΰ�
			cur = cur->right;
		}else if (cur->key > key) {
			par = cur; // cur �̵����� �θ� ǥ���صΰ�
			cur = cur->left;
		}
	} 
	//while�� �������ϱ� cur->key == key ��� ��
	printf("���� �� : %d\n", cur->key);

	// �¿��� ��� X �쿡�� ��� X :  key �� ���� ��尡 Leaf Node �϶�
	if (cur->left == 0 && cur->right == 0) {

	}
	// �°� �ְ� �찡 ������, �°� ���� �찡 �ִ��� (else if�̱⶧���� �Ѵ� �ִ°Ŵ� �̹� �ɷ����� �ٽ� �ȵ���)
	else if (cur->left == 0 || cur->right == 0) {
	}

	// �¿��� ��� O �쿡�� ��� O 
	else if (cur->left != 0 && cur->right != 0) {



}


int KeyCheck(Tree* tree, int key) {	
	// �Է��� Ű���� ���� ��尡 �ִ��� ������ Ȯ���ϴ� �Լ�
	int result = -1;
	Node* cur = tree->root;
	while (1) {
		if (cur->key == key) {
			result = 1;
			return result;
		}
		if (cur->key > key) {
			if (cur->left == 0)
			// �Է¹��� Ű���� ������ Ű������ ������ ������->left�� ���� ?? �� �ȵǴ°�����
				return result;
			cur = cur->left;

		}
		if (cur->key < key) {
			if (cur->right == 0)
				return result;
			cur = cur->right;
		}
	}
}

void main() {
	Tree * tree = CreateTree();

	AddKey(tree, 40);
	AddKey(tree, 20);
	AddKey(tree, 30);
	AddKey(tree, 10);
	AddKey(tree, 9);
	DeleteKey(tree, 20);
	PrintTree(tree);


}



