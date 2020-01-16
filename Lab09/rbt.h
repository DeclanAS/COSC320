#ifndef RBT_H
#define RBT_H

/* Name: Declan Sheehan
 * Course: COSC320-001
 * Desc: rbt.h that holds the entire RBT class, and
 * separate functions for formmating and functionality.
 * 
 */

enum color_t { // Identifies node's color.
	RED, // 0
	BLACK // 1
};

char RorB(color_t colour){ // Returns desired char for color.
	if(colour == 0)
		return 'R';
	else if (colour == 1)
		return 'B';
	else
		return '*';
}

class RBTree{ // Class declaration.
	private:
		struct TreeNode { // Node
			int key;
			color_t color;
			TreeNode* left;
			TreeNode* right;
			TreeNode* parent;
		};
		TreeNode* root = NULL;
		static TreeNode* const nil;

		int TreeSize = 0; // Keeps track of # of nodes in RBT.

		void RBTInsert(TreeNode* z); // Insert node `z`.
		void RBTInsertFixup(TreeNode* z); // Insert SR for balance.

		void Ordering(int choice); // IO/PR/PO based off Print().
		void Inorder(TreeNode* a); // Inorder printout.
		void Preorder(TreeNode* a); // Preorder printout.
		void Postorder(TreeNode* a); // Postorder printout.

		TreeNode* Search(TreeNode* a, int b); // Search method
		TreeNode* Search_Private(int a); // Private search method.

		TreeNode* minimumnode(); // Returns min node.
		TreeNode* maximumnode(); // Returns max node.
		int minimumkey(TreeNode* n); // Returns min key.
		int maximumkey(TreeNode* n); // Returns max key.
		TreeNode* minimumnode(TreeNode* n); // Min SR func.
		TreeNode* maximumnode(TreeNode* n); // Max SR func.

		void LeftRotate(TreeNode* x); // Left rotation method.
		void RightRotate(TreeNode* y); // Right rotation method.

		void deleteRBT(TreeNode* a); // Deletes entire RBT.
		void RBTDelete(TreeNode* z); // Deletes node.
		void RBDeleteFixup(TreeNode* x); // SR deleting node.
		void RBTTransplant(TreeNode* u, TreeNode* v); // SR deleting node.
		TreeNode* Successor(TreeNode* a); // Finds Succ of node a.


	public:
		RBTree(); // Constructor.
		~RBTree(); // Destructor.

		void Print(int a); // Prints Inorder/Preorder/Postorder.
		void Printlevels(); // Prints ~8 nodes from RBT.

		int minimumkey(); // Returns minimum key.
		int maximumkey(); // Returns maximum key.

		void Insert(int a); // Inserts node with value `a`.
		void deleteNode(int a); // Deletes a node with value `a`.

		int Successor(int a); // Returns successor of node.

		bool Search(int a); // Returns true if node found; vice versa.
		void delallnil(); // DEALLOCATES NIL NODE. FUN FACT: THE PROGRAM
		/* LEAKS 32 BYTES IF THE MAIN IS ENTIRELY EMPTY BECAUSE NIL STILL
			ALLOCATES DATA. THERE'S NO NEED HONESTLY.
		*/
};

RBTree::TreeNode* const RBTree::nil = new TreeNode({0, BLACK, nullptr, nullptr, nullptr});

RBTree::RBTree(){ // Constructor.
	root = nil;
	root->parent = nil;
	TreeSize = 0;
}

RBTree::~RBTree(){ // Destructor.
	deleteRBT(root);
	// delete RBTree::nil; <-- Gives lots of valgrind errors. :)
	// (If class made multiple times).
}

void RBTree::delallnil(){ // Deletes nil; deallocating.
	delete RBTree::nil;
}

void RBTree::Insert(int value){ // Insertion method.
	TreeNode* node = new TreeNode;
	node->key = value;
	RBTInsert(node);
	TreeSize++;
}

void RBTree::deleteNode(int value){ // Deletion method.
	TreeNode* node = Search_Private(value);
	RBTDelete(node);
	delete node;
}

RBTree::TreeNode* RBTree::Successor(TreeNode* n){ // Successor method.
	if(n == RBTree::nil){
		; // I guess this works.
	} else if(n->right != RBTree::nil) {
		return minimumnode(n->right);
	} else if (n == maximumnode(root)){
		return n;
	} else if (n == n->parent->right){
		while(n != n->parent->left)
			n = n->parent;
		return n->parent;
	} else if (n == n->parent->left)
		return n->parent;
}

int RBTree::Successor(int a){ // Public successor method.
	TreeNode* Succ1 = Search_Private(a);
	TreeNode* Succ2 = Successor(Succ1);
	return Succ2->key;
}

RBTree::TreeNode* RBTree::Search(TreeNode* n, int value){ // Search method.
	if(n != RBTree::nil && n != NULL){
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

RBTree::TreeNode* RBTree::Search_Private(int value){ // Search method
	return Search(root, value); // Don't really need this func, but hey.
}

bool RBTree::Search(int value){ // Public search method.
	TreeNode* Ser = Search_Private(value);
	if(Ser == NULL || Ser == RBTree::nil)
		return false;
	else
		return true;
}

void RBTree::Printlevels(){ // Prints ~8 Nodes of the RBT
	bool Lsib;
	bool Rsib;
	bool Tabs = true;
	if(TreeSize == 0){ // If empty, print `empty`.
		printf("\t\t\t\t\tTree Is Empty\n");
		return;
	}
	TreeNode* n = root;
	if(root != NULL) // Printing root node.
		printf("\t\t\t\t\t%d%c\n", root->key, RorB(root->color));

	if(root->left != RBTree::nil){ // Printing root's left child.
		n = n->left;
		printf("\t\t\t\t%d%c", n->key, RorB(n->color));
		n = n->parent;
		Lsib = true;
	} else { // Else if it does not exist.
		printf("\t\t\t\t X ");
		Lsib = false; // Prevents printing this node's subtree.
	}

	if(root->right != RBTree::nil){ // Prints root's right child.
		n = n->right;
		printf("\t\t%d%c\n", n->key, RorB(n->color));
		n = n->parent;
		Rsib = true;
	} else { // Else if it does not exist.
		printf("\t\t X \n");
		Rsib = false; // Prevents printing this node's subtree.
	}

	if(Lsib == false && Rsib == false) // For formatting purposes.
		Tabs = false;

	if(Lsib == true){
		if(root->left->left != RBTree::nil){ // Prints root's LL child.
			n = n->left->left;
			printf("\t\t\t%d%c", n->key, RorB(n->color));
			n = n->parent;
		} else { // Else if it does not exist.
			printf("\t\t\t X ");
		}
		n = root;
		if(root->left->right != RBTree::nil){ // Prints root's LR child.
			n = n->left->right;
			printf("\t%d%c", n->key, RorB(n->color));
			n = n->parent->parent;
		} else { // Else if it does not exist.
			printf("\t X ");
		}
	} else { // Else if the root's left child's child does not exist.
		if(Tabs == true)
			printf("\t\t\t  \t");
	}

	if(Rsib == true){
		if(root->right->left != RBTree::nil){ // Prints root's RL child.
			n = n->right->left;
			printf("\t\t%d%c", n->key, RorB(n->color));
			n = n->parent;
		} else { // Else if it does not exist.
			printf("\t\t X ");
		}
		n = root;
		if(root->right->right != RBTree::nil){ // Prints root's RR child.
			n = n->right->right;
			printf("\t%d%c\n", n->key, RorB(n->color));
		} else { // Else if it does not exist.
			printf("\t X \n");
		}
	} else { // Else if the root's right child's child does not exist.
		if(Tabs == true)
			printf("\n");
	}
}

void RBTree::RBTInsertFixup(TreeNode* z){ // Insert fixup method.
	while(z->parent->color == RED){
		if(z->parent == z->parent->parent->left){
			TreeNode* y = z->parent->parent->right;
			if(y->color == RED){
				z->parent->color = BLACK;
				y->color = BLACK;
				z->parent->parent->color = RED;
				z = z->parent->parent;
			} else {
				if (z == z->parent->right){
					z = z->parent;
					LeftRotate(z);
				}
				z->parent->color = BLACK;
				z->parent->parent->color = RED;
				RightRotate(z->parent->parent);
			}
		} else { // SAME AS THEN CLAUSE W/ RIGHT<->LEFT
			TreeNode* y = z->parent->parent->left;
			if(y->color == RED){
				z->parent->color = BLACK;
				y->color = BLACK;
				z->parent->parent->color = RED;
				z = z->parent->parent;
			} else {
				if (z == z->parent->left){
					z = z->parent;
					RightRotate(z);
				}
				z->parent->color = BLACK;
				z->parent->parent->color = RED;
				LeftRotate(z->parent->parent);
			}
		}
	}
	root->color = BLACK;
}

void RBTree::RBTInsert(TreeNode* z){ // Insert method.
	TreeNode* y = RBTree::nil;
	TreeNode* x = RBTree::root;
	while(x != RBTree::nil){
		y = x;
		if(z->key < x->key)
			x = x->left;
		else
			x = x->right;
	}
	z->parent = y;
	if(y == RBTree::nil)
		root = z;
	else if (z->key < y->key)
		y->left = z;
	else
		y->right = z;
	z->left = RBTree::nil;
	z->right = RBTree::nil;
	z->color = RED;
	RBTInsertFixup(z);
}

void RBTree::Inorder(TreeNode* n){ // Prints in inorder.
	if(n != nil){
		Inorder(n->left);
		if(n->color == 0)
			std::cout << n->key << "{\033[1;31m" << RorB(n->color) << "\033[0m} ";
		else
			std::cout << n->key << "{\033[1;30m" << RorB(n->color) << "\033[0m} ";
		Inorder(n->right);
	}
}

void RBTree::Preorder(TreeNode* n){ // Prints in preorder.
	if(n != nil){
		if(n->color == 0)
			std::cout << n->key << "{\033[1;31m" << RorB(n->color) << "\033[0m} ";
		else
			std::cout << n->key << "{\033[1;30m" << RorB(n->color) << "\033[0m} ";
		Preorder(n->left);
		Preorder(n->right);
	}
}

void RBTree::Postorder(TreeNode* n){ // Prints in postorder.
	if(n != nil){
		Postorder(n->left);
		Postorder(n->right);
		if(n->color == 0)
			std::cout << n->key << "{\033[1;31m" << RorB(n->color) << "\033[0m} ";
		else
			std::cout << n->key << "{\033[1;30m" << RorB(n->color) << "\033[0m} ";
	}
}

void RBTree::Ordering(int choice){ // Private `print` method.
	if(choice == 1){
		std::cout << "Inorder: ";
		Inorder(root);
		printf("\n");
	} else if (choice == 2) {
		std::cout << "Preorder: ";
		Preorder(root);
		printf("\n");
	} else if (choice == 3) {
		std::cout << "Postorder: ";
		Postorder(root);
		printf("\n");
	} else {
		printf("Invalid option.\n");
	}
}

RBTree::TreeNode* RBTree::minimumnode(TreeNode* n){ // Minimum node method.
	TreeNode* temp;
	TreeNode* y;
	temp = n;
	y = NULL;
	while(temp != RBTree::nil){
		y = temp;
		temp = temp->left;
	}
	return y;
}

RBTree::TreeNode* RBTree::maximumnode(TreeNode* n){ // Maximum node method.
	TreeNode* temp;
	TreeNode* y;
	temp = n;
	y = NULL;
	while(temp != RBTree::nil){
		y = temp;
		temp = temp->right;
	}
	return y;
}

RBTree::TreeNode* RBTree::minimumnode(){ // Minimum node caller.
	return minimumnode(root);
}

RBTree::TreeNode* RBTree::maximumnode(){ // Maximum node caller.
	return maximumnode(root);
}

int RBTree::minimumkey(TreeNode* n){ // Private minimum key method.
	TreeNode* temp;
	TreeNode* y;
	temp = n;
	y = NULL;
	while(temp != RBTree::nil){
		y = temp;
		temp = temp->left;
	}
	return y->key;
}

int RBTree::maximumkey(TreeNode* n){ // Private maximum key method.
	TreeNode* temp;
	TreeNode* y;
	temp = n;
	y = NULL;
	while(temp != RBTree::nil){
		y = temp;
		temp = temp->right;
	}
	return y->key;
}

int RBTree::minimumkey(){ // Public minimum key method.
	return minimumkey(root);
}

int RBTree::maximumkey(){ // Public maximum key method.
	return maximumkey(root);
}

void RBTree::Print(int choice){ // Public print method.
	Ordering(choice);
}

void RBTree::RBTTransplant(TreeNode* u, TreeNode* v){ // Transplant method.
	if(u->parent == RBTree::nil)
		root = v;
	else if(u == u->parent->left)
		u->parent->left = v;
	else
		u->parent->right = v;
	v->parent = u->parent;
}

void RBTree::LeftRotate(TreeNode* x){ // Left rotate method.
	TreeNode* y = x->right;
	x->right = y->left;
	if(y->left != RBTree::nil)
		y->left->parent = x;
	y->parent = x->parent;
	if (x->parent == RBTree::nil)
		root = y;
	else if (x == x->parent->left)
		x->parent->left = y;
	else
		x->parent->right = y;
	y->left = x;
	x->parent = y;
}

void RBTree::RightRotate(TreeNode* x){ // Right rotate method.
	TreeNode* y = x->left;
	x->left = y->right;
	if(y->left != RBTree::nil)
		y->right->parent = x;
	y->parent = x->parent;
	if(x->parent == RBTree::nil)
		root = y;
	else if (x == x->parent->right)
		x->parent->right = y;
	else
		x->parent->left = y;
	y->right = x;
	x->parent = y;
}

void RBTree::RBDeleteFixup(TreeNode* x){ // Delete fixup method.
	while(x != root && x->color == BLACK){
		if(x == x->parent->left){
			TreeNode* w = x->parent->right;
			if(w->color == RED){
				w->color = BLACK;
				x->parent->color = RED;
				LeftRotate(x->parent);
				w = w->parent->right;
			}
			if(w->left->color == BLACK && w->right->color == BLACK){
				w->color = RED;
				x = w->parent;
			} else {
				if (w->right->color == BLACK){
					w->left->color = BLACK;
					w->color = RED;
					RightRotate(w);
					w = x->parent->right;
				}
				w->color = x->parent->color;
				x->parent->color = BLACK;
				w->right->color = BLACK;
				LeftRotate(x->parent);
				x = root;
			}
		} else { // SAME AS THEN CLAUSE WITH RIGHT<->LEFT
			TreeNode* w = x->parent->left;
			if(w->color == RED){
				w->color = BLACK;
				x->parent->color = RED;
				RightRotate(x->parent);
				w = w->parent->left;
			}
			if(w->right->color == BLACK && w->left->color == BLACK){
				w->color = RED;
				x = w->parent;
			} else {
				if (w->left->color == BLACK){
					w->right->color = BLACK;
					w->color = RED;
					LeftRotate(w);
					w = x->parent->left;
				}
				w->color = x->parent->color;
				x->parent->color = BLACK;
				w->left->color = BLACK;
				RightRotate(x->parent);
				x = root;
			}
		}
	}
	x->color = BLACK;
}

void RBTree::RBTDelete(TreeNode* z){ // Delete node method.
	TreeNode* x;
	TreeNode* y = z;
	int y_original_color = y->color;
	if(z->left == RBTree::nil){
		x = z->right;
		RBTTransplant(z, z->right);
	} else if (z->right == RBTree::nil) {
		x = z->left;
		RBTTransplant(z, z->left);
	} else {
		y = minimumnode(z->right);
		y_original_color = y->color;
		x = y->right;
		if(y->parent == z){
			x->parent = y;
		} else {
			RBTTransplant(y, y->right);
			y->right = z->right;
			y->right->parent = y;
		}
		RBTTransplant(z, y);
		y->left = z->left;
		y->left->parent = y;
		y->color = z->color;
	}
	if(y_original_color == BLACK)
		RBDeleteFixup(x);
	TreeSize--;
}

void RBTree::deleteRBT(TreeNode* n){ // Delete entire RBT method.
	if(n != RBTree::nil){
		deleteRBT(n->left);
		deleteRBT(n->right);
		delete n;
	}
}

#endif
