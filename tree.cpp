#include "tree.h"

#pragma region CONSTRUCTORS/DESTRUCTOR


Binary_search_tree::Binary_search_tree() {
	root = nullptr;
}


Binary_search_tree::~Binary_search_tree() {
	destructor_helper(root);
}


void Binary_search_tree::destructor_helper(Node * root) {
	if (root) {
		destructor_helper(root->left);
		destructor_helper(root->right);
		delete root;
	}
}


#pragma endregion
#pragma region INSERT


void Binary_search_tree::insert(int val) {
	if (!root) {
		Node * new_root = new Node;
		new_root->val = val;
		root = new_root;
	}
	else {
		insert_helper(root, val);
	}
}


void Binary_search_tree::insert_helper(Node *& root, int val) {
	if (!root) {
		Node * new_root = new Node;
		new_root->val = val;
		root = new_root;
	}
	else if (val < root->val) {
		insert_helper(root->left, val);
	}
	else {
		insert_helper(root->right, val);
	}
}


#pragma endregion
#pragma region REMOVE


bool Binary_search_tree::remove(int val) {
	Node * temp = get_node(val);
	if (!temp) {
		return false;
	}
	else if (!temp->left && !temp->right) {
		delete_leaf(temp);
	}
	else if (temp->left && !temp->right || temp->right && !temp->left) {
		delete_single_parent(temp);
	}
	else {
		delete_double_parent(temp);
	}
	return true;
}


void Binary_search_tree::delete_leaf(Node * temp) {
	Node * prev = get_prev_node(temp);
	if (prev->left == temp) {
		delete temp;
		prev->left = nullptr;
	}
	else {
		delete temp;
		prev->right = nullptr;
	}
}


void Binary_search_tree::delete_single_parent(Node * temp) {
	Node * prev = get_prev_node(temp);
	if (prev->left == temp) {
		if (temp->left) {
			prev->left = temp->left;
		}
		else {
			prev->left = temp->right;
		}
	}
	else {
		if (temp->left) {
			prev->right = temp->left;
		}
		else {
			prev->right = temp->right;
		}
	}
}


void Binary_search_tree::delete_double_parent(Node * temp) {
	Node * min = temp->right;
	while (min->left) {
		min = min->left;
	}
	temp->val = min->val;
	Node * prev = get_prev_node(min);
	prev->left = nullptr;
}


#pragma endregion
#pragma region SEARCHES


bool Binary_search_tree::search(int val) {
	Node * temp = get_node(val);
	if (!temp) {
		return false;
	}
	return true;
}

Node * Binary_search_tree::get_node(int val) {
	Node * temp = root;
	while (temp != nullptr && temp->val != val) {
		if (val < temp->val) {
			temp = temp->left;
		}
		else {
			temp = temp->right;
		}
	}
	return temp;
}


Node * Binary_search_tree::get_prev_node(Node * temp) {
	Node * prev = root;
	while (prev->left != temp && prev->right != temp) {
		if (temp->val < prev->val) {
			prev = prev->left;
		}
		else {
			prev = prev->right;
		}
	}
	return prev;
}


#pragma endregion
#pragma region TRAVERSAL


void Binary_search_tree::in_order() {
	if (!root) {
		printf("Tree is empty");
	}
	else {
		in_order_helper(root);
	}
	printf("\n");
}


void Binary_search_tree::in_order_helper(Node * root) {
	if (root) {
		in_order_helper(root->left);
		printf("%d ", root->val);
		in_order_helper(root->right);
	}
}


void Binary_search_tree::pre_order() {
	if (!root) {
		printf("Tree is empty");
	}
	else {
		pre_order_helper(root);
	}
	printf("\n");
}


void Binary_search_tree::pre_order_helper(Node * root) {
	if (root) {
		printf("%d ", root->val);
		pre_order_helper(root->left);
		pre_order_helper(root->right);
	}
}


void Binary_search_tree::post_order() {
	if (!root) {
		printf("Tree is empty");
	}
	else {
		post_order_helper(root);
	}
	printf("\n");
}


void Binary_search_tree::post_order_helper(Node * root) {
	if (root) {
		post_order_helper(root->left);
		post_order_helper(root->right);
		printf("%d ", root->val);
	}
}


#pragma endregion