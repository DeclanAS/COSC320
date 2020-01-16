#ifndef BT_T
#define BT_T
#include <iostream>
#include <stdlib.h>

/*	Name: Declan Sheehan
 *	Course: COSC320-001
 *	Desc: Holds all the decl. and def. of the BT class.
 */


class BinaryTree{
	private:
		struct TreeNode {
			int key;
			TreeNode* left = NULL;
			TreeNode* right = NULL;
			TreeNode* parent = NULL;
		} TN;
		TreeNode* root;
		int TreeSize;


		int minimum(TreeNode* a);
		int maximum(TreeNode* a);

		TreeNode* minimum2(TreeNode* a);
		TreeNode* maximum2(TreeNode* a);

		void Inorder(TreeNode* a);
		void Preorder(TreeNode* a);
		void Postorder(TreeNode* a);
		void deleteBT(TreeNode* a);
		void Insert(TreeNode* a, int b);
		TreeNode* Search(TreeNode* a, int b);
		void Transplant(TreeNode* a, TreeNode* b);
		void Deleteus(TreeNode* a);
	public:
		BinaryTree();
		~BinaryTree();

		void Test();

		void Deleteus(int a);
		void Print(int a);

		int minimum();
		int maximum();

		void Ordering(int a);
		void Insert(int a);
		int Successor(int a);
		TreeNode* Search(int a);

};

// ========================================== //
// ============== DEFINITIONS =============== //
// ========================================== //

static int pos = 0;

BinaryTree::BinaryTree(){
	root = NULL;
	TreeSize = 0;
}

BinaryTree::~BinaryTree(){
	deleteBT(root);
}

void BinaryTree::deleteBT(TreeNode* n){
	if(n != NULL){
		deleteBT(n->left);
		deleteBT(n->right);
		delete n;
	}
}

void BinaryTree::Insert(TreeNode* n, int value){
	if(root == NULL){
		root = n;
	} else {
		TreeNode* A = root;
		TreeNode* B = root;
		while(A){
			B = A;
			if(n->key <= A->key)
				A = A->left;
			else if(n->key > A->key)
				A = A->right;
		}
		if(n->key <= B->key)
			B->left = n;
		else if(n->key > B->key)
			B->right = n;
		n->parent = B;
	}
}
/*2nd line below is the origin of the unintialized
	conditional jumping. */
void BinaryTree::Insert(int value){
	TreeNode* node = new TreeNode;
	node->key = value;
	Insert(node, value);
	TreeSize++;
}

BinaryTree::TreeNode* BinaryTree::Search(TreeNode* n, int value){
	if(n != NULL){
		if(value == n->key)
			return n;
		if(value < n->key)
			return Search(n->left, value);
		else
			return Search(n->right, value);
	} else {
		return NULL;
	}
}

BinaryTree::TreeNode* BinaryTree::Search(int value){
	return Search(root, value);
}

int BinaryTree::minimum(TreeNode* n){
	TreeNode* temp = new TreeNode;
	TreeNode* y = new TreeNode;
	temp = n;
	y = NULL;
	while(temp != NULL){
		y = temp;
		temp = temp->left;
	}
	return y->key;
}

BinaryTree::TreeNode* BinaryTree::minimum2(TreeNode* n){
	TreeNode* temp = new TreeNode;
	TreeNode* y = new TreeNode;
	temp = n;
	y = NULL;
	while(temp != NULL){
		y = temp;
		temp = temp->left;
	}
	return y;
}

int BinaryTree::minimum(){
	return minimum(root);
}

int BinaryTree::maximum(TreeNode* n){
	TreeNode* temp = new TreeNode;
	TreeNode* y = new TreeNode;
	temp = n;
	y = NULL;
	while(temp != NULL){
		y = temp;
		temp = temp->right;
	}
	return y->key;
}

BinaryTree::TreeNode* BinaryTree::maximum2(TreeNode* n){
	TreeNode* temp = new TreeNode;
	TreeNode* y = new TreeNode;
	temp = n;
	y = NULL;
	while(temp != NULL){
		y = temp;
		temp = temp->right;
	}
	return y;
}

int BinaryTree::maximum(){
	return maximum(root);
}

int BinaryTree::Successor(int value){
	TreeNode* n = Search(value);
	if(n == NULL){
		; // I guess this works.
	} else if(n->right != NULL) {
		return (minimum2(n->right))->key;
	} else if (n == maximum2(root)){
		return n->key;
	} else if (n == n->parent->right){
		while(n != n->parent->left)
			n = n->parent;
		return n->parent->key;
	} else if (n == n->parent->left)
		return n->parent->key;
}

void BinaryTree::Inorder(TreeNode* n){
	if(n != NULL){
		Inorder(n->left);
		std::cout << n->key << " ";
		Inorder(n->right);
	}
}

void BinaryTree::Preorder(TreeNode* n){
	if(n != NULL){
		std::cout << n->key << " ";
		Preorder(n->left);
		Preorder(n->right);
	}
}

void BinaryTree::Postorder(TreeNode* n){
	if(n != NULL){
		Postorder(n->left);
		Postorder(n->right);
		std::cout << n->key << " ";
	}
}

void BinaryTree::Ordering(int choice){
	if(choice == 1){
		std::cout << "Inorder: ";
		Inorder(root);
	} else if (choice == 2) {
		std::cout << "Preorder: ";
		Preorder(root);
	} else if (choice == 3) {
		std::cout << "Postorder: ";
		Postorder(root);
	} else {
		printf("Invalid option.\n");
	}
}

void BinaryTree::Print(int choice){
	Ordering(choice);
}

void BinaryTree::Transplant(TreeNode* u, TreeNode* v){
	if(u->parent == NULL)
		root = v;
	else if(u == u->parent->left)
		u->parent->left = v;
	else
		u->parent->right = v;
	if(v != NULL){
		v->parent = u->parent;
	}
}

void BinaryTree::Deleteus(TreeNode* n){
	if(n == NULL){
		std::cout << "Cannot delete.\n";
		return;
	} else {
		TreeNode* A = n;
		TreeNode* B = n;
		if(n->left == NULL || n->right == NULL){
			A = n;
		} else {
			int a = Successor(n->key);
			A = Search(a);
		}
		if(A->left != NULL){
			B = A->left;
		} else if (A->right != NULL){
			B = A->right;
		}
		Transplant(B, A);

		if(A != B){
			n->key = A->key;
		}
		if(A->parent != NULL){ // Setting our node to delete to NULL
			TreeNode* temp = A->parent;
			if(temp->right)
				if((temp->right)->key == A->key)
					temp->right = NULL;

			if(temp->left)
				if((temp->left)->key == A->key)
					temp->left = NULL;
		}
		delete A;
		TreeSize--;
	}
}

void BinaryTree::Test(){
	if(root == NULL)
		std::cout << "NULL" << std::endl;
	if(root->right != NULL)
		std::cout << root->right->key << std::endl;
	else
		std::cout << "NO RIGHT" << std::endl;

	if(root->left != NULL)
		std::cout << root->left->key << std::endl;
	else
		std::cout << "NO LEFT" << std::endl;
}

void BinaryTree::Deleteus(int value){
	TreeNode* X = Search(value);
	if(X == NULL){
		printf("No node with value.\n");
		return;
	} else
		Deleteus(X);
}

#endif
