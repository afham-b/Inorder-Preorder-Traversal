#include <iostream>
#include <string>
using namespace std;

class BSTree {
private:

	// Sub-class to represent nodes within the tree
	class node {
	public:
		string data;
		node* left;
		node* right;
		node () { left = right = nullptr; }
	};

	// Pointer to the root node, initially NULL
	node* root;

	// Destroys the subtree at the given node (initiallycalled by the
	//	destructor).
	void destroy (const node* p) {
		if (p) {
			destroy(p->left);
			destroy(p->right);
			delete p;
		}
	}

	// Finds a node in a given subtree. Returns true/false to indicate if
	//	node with given string is in the subtree.
	bool find (const string& s, node* p) const {
		// Given: p is a pointer to an existing node
		if (s == p->data)
			return true;
		if (s < p->data)
			return p->left && find(s, p->left);
		return p->right && find(s, p->right);
	}

	// Inserts a new node into the subtree at the given pointer.
	void insert (const string& s, node* p) {
		// Given: p is a pointer to an existing node (root of a subtree)
		if (s < p->data) { // Insert into left subtree
			if (p->left) // Left subtree exists
				insert(s, p->left);
			else { // No left subtree, insert the new node
				p->left = new node;
				p->left->data = s;
			}
		}
		else if (s > p->data) { // Insert into right subtree
			if (p->right)
				insert(s, p->right);
			else {
				p->right = new node;
				p->right->data = s;
			}
		}
	}

	// Performs an inorder traversal of the subtree at node p. For each node
	//	prints the string stored at that node.
	void print_inorder (node* p) const {
		// Print all values in subtree, in order
		if (p) {
			print_inorder(p->left);
			cout << p->data << endl;
			print_inorder(p->right);
		}
	}

	// Perform a preorder traversal of the subtree at node p, also given the
	//	depth at node p. For each node, prints the string stored at the node
	//	with prefix showing the depth.
	void print_preorder (node* p, size_t depth) const {
		if (p) {
			for (size_t i = 0; i < depth; i++)
				cout << '-';
			cout << p->data << endl;
			print_preorder(p->left, depth + 1);
			print_preorder(p->right, depth + 1);
		}
	}

public:

	// Constructor - Sets the root node to NULL
	BSTree() { root = nullptr; }

	// Destructor - Deletes all nodes allocated by the tree
	~BSTree () { destroy(root); } // see private member function: destroy

	// Find a string in the tree. Returns true/false to indicate if the given
	//	string is in the tree.
	bool find (const string& s) const {
		return root && find(s, root);
	}

	// Inserts a string into the tree. If the string already exists in the
	//	tree, does nothing.
	void insert (const string& s) {
		// Is tree empty?
		if (!root) {
			root = new node;
			root->data = s;
		}
		else if (s < root->data) {
			// New node goes on left side of root
			if (root->left) // If there is a left subtree
				insert(s, root->left);
			else { // No left subtree, create node
				root->left = new node;
				root->left->data = s;
			}
		}
		else if (s > root->data) {
			if (root->right)
				insert(s, root->right);
			else {
				root->right = new node;
				root->right->data = s;
			}
		}
	}

	// Perform an inorder traversal on the tree. The traversal simply prints
	//	the string stored at each node.
	void print_inorder () const { print_inorder(root); }

	// Perform a preorder traversal, printing strings stored at each node
	//	while showing tree structure.
	void print_preorder () const { print_preorder(root, 0); }

	// TODO: Implement these functions...

	// Returns the height of the tree (longest path from root to a leaf)
	size_t height () const { return 0; }

	// Returns the number of leaf nodes in the tree
	size_t leaves () const { return 0; }

	// Returns the string stored in the parent node of the node with the
	//	given string. If the given string does not exist in the tree, or
	//	exists in the root, returns an empty string.
	string parent (const string& s) const { return string(); }

	// Returns the string stored in the sibling node of the node with the
	//	given string. If the given string does not exist in the tree, or
	//	exists in a node that has no sibling node, returns an empty string.
	string sibling (const string& s) const { return string(); }
};

int main () {
	BSTree tree;
	string s;

	cout << "Enter strings to insert into the binary search tree.\n";
	cout << "When finished, press ENTER.\n\n";
	cout << "> ";
	getline(cin, s);
	while (s.size()) {
		tree.insert(s);
		cout << "> ";
		getline(cin, s);
	}

	cout << "\nAn inorder traversal:\n";
	tree.print_inorder();

	cout << "\nA preorder traversal:\n";
	tree.print_preorder();

	return 0;
}
