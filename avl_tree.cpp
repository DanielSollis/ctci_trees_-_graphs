#include "avl_tree.h"
#include <iostream>
#include <algorithm>

#pragma region PROTOTYPES


AVL_node * create_node(int val);
AVL_node * insert_leaf(int val, AVL_node * root);
bool is_unbalanced(AVL_node * left, AVL_node * right);
std::vector<AVL_node *> get_xyz(AVL_node * it, int val);
void fix_heights(AVL_node * it);
int get_height(AVL_node * node);


#pragma endregion

#pragma region INSERT


void AVL_Tree::insert(int val) {
	if (!root) {
		AVL_node * new_root = create_node(val);
		new_root->parent = nullptr;
		root = new_root;
	}
	else {
		AVL_node * it;
		it = insert_leaf(val, root);
		fix_heights(it);
		bool unbalenced = false;
		while (!unbalenced && it) {
			if (is_unbalanced(it->left, it->right)) {
				unbalenced = true;
				std::vector<AVL_node *> xyz = get_xyz(it, val);
				do_rotations(xyz[0], xyz[1], xyz[2]);
			}
			it = it->parent;
		}
	}
}


AVL_node * create_node(int val) {
	AVL_node * new_node = new AVL_node;
	new_node->data = val;
	new_node->height = 1;
	new_node->left = nullptr;
	new_node->right = nullptr;
	return new_node;
}


AVL_node * insert_leaf(int val, AVL_node * root) {
	AVL_node * it = root;
	AVL_node * prev = it;
	while (it) {
		prev = it;
		it->data < val ? it = it->left : it = it->right;
	}
	AVL_node * new_leaf = create_node(val);
	new_leaf->parent = prev;
	it = new_leaf;
	prev->data < val ? prev->left = it : prev->right = it;
	return it;
}


void fix_heights(AVL_node * it) {
	AVL_node * prev = it;
	it = it->parent;
	while (it) {
		it->height = prev->height + 1;
		prev = it;
		it = it->parent;
	}
}


bool is_unbalanced(AVL_node * left, AVL_node * right) {
	if (left && right) {
		if (left->height - 1 > right->height || right->height - 1 > left->height) {
			return true;
		}
	}
	else if (left && !right || !left && right) {
		AVL_node * child;
		left ? child = left : child = right;
		if (child->height > 1) {
			return true;
		}
	}
	return false;
}


#pragma endregion


bool AVL_Tree::remove(int val) {
	return false;
}


AVL_node * AVL_Tree::search(int val) {
	return nullptr;
}


#pragma region ROTATIONS


std::vector<AVL_node *> get_xyz(AVL_node * it, int val) {
	std::vector<AVL_node *> xyz;
	for (int i = 0; i < 3; ++i) {
		xyz.push_back(it);
		it->data < val ? it = it->left : it = it->right;
	}
	return xyz;
}


void AVL_Tree::do_rotations(AVL_node * z, AVL_node * y, AVL_node * x) {
	if (z->left == y && y->left == x) {
		right_rotation(z);
	}
	else if (z->left == y && y->right == x) {
		left_rotation(y);
		right_rotation(z);
	}
	else if (z->right == y && y->right == x) {
		left_rotation(z);
	}
	else if (z->right == y && y->left == x) {
		right_rotation(y);
		left_rotation(z);
	}
}

/*
		x
	y
z

x left becomes 2
y left becomes x
y parent becomes x parent
x parent becomes y
*/
void AVL_Tree::left_rotation(AVL_node * pivot) {
	
}


void AVL_Tree::right_rotation(AVL_node * pivot) {

}


int get_height(AVL_node * node) {
	if (node) {
		return node->height;
	}
	return 0;
}


#pragma endregion


std::vector<std::vector<AVL_node *>> AVL_Tree::get_levels() {
	std::vector<std::vector<AVL_node *>> depths;
		std::vector<AVL_node *> root_depth;
		if (!root) {
			return depths;
		}
		root_depth.push_back(root);
		depths.push_back(root_depth);
		int depth = 0;
		bool done = false;
		while (!done) {
			done = true;
			std::vector<AVL_node *> current_depth;
			for (auto node : depths[depth]) {
				if (node->left) {
					current_depth.push_back(node->left);
				}
				if (node->right) {
					current_depth.push_back(node->right);
				}
			}
			if (current_depth.size() != 0) {
				depths.push_back(current_depth);
				depth++;
				done = false;
			}
		}
		return depths;
}