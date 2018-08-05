#include "tree.h"
#include <map>
#include <iostream>
#include <stdlib.h>


#pragma region CONSTRUCTORS/DESTRUCTOR


Tree::Tree() {
	root = nullptr;
}


Tree::~Tree() {
	destructor_helper(root);
}


void Tree::destructor_helper(Tree_node * root) {
	if (root) {
		destructor_helper(root->left);
		destructor_helper(root->right);
		delete root;
	}
}


#pragma endregion
#pragma region INSERT


void Tree::insert(int val) {
	if (!root) {
		Tree_node * new_root = new Tree_node;
		new_root->val = val;
		root = new_root;
	}
	else {
		insert_helper(root, val);
	}
}


void Tree::insert_helper(Tree_node *& root, int val) {
	if (!root) {
		Tree_node * new_root = new Tree_node;
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


bool Tree::remove(int val) {
	Tree_node * temp = get_node(val);
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


void Tree::delete_leaf(Tree_node * temp) {
	Tree_node * prev = get_prev_node(temp);
	if (prev->left == temp) {
		delete temp;
		prev->left = nullptr;
	}
	else {
		delete temp;
		prev->right = nullptr;
	}
}


void Tree::delete_single_parent(Tree_node * temp) {
	Tree_node * prev = get_prev_node(temp);
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


void Tree::delete_double_parent(Tree_node * temp) {
	Tree_node * min = temp->right;
	while (min->left) {
		min = min->left;
	}
	temp->val = min->val;
	Tree_node * prev = get_prev_node(min);
	prev->left = nullptr;
}


#pragma endregion
#pragma region SEARCHES


bool Tree::search(int val) {
	Tree_node * temp = get_node(val);
	if (!temp) {
		return false;
	}
	return true;
}

Tree_node * Tree::get_node(int val) {
	Tree_node * temp = root;
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


Tree_node * Tree::get_prev_node(Tree_node * temp) {
	Tree_node * prev = root;
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


std::vector<int> Tree::in_order(Tree_node * node) {
	std::vector<int> result;
	if (!root) {
		return result;
	}
	else {
		node ? in_order_helper(node, result) : in_order_helper(root, result);
	}
	return result;
}


void Tree::in_order_helper(Tree_node * node, std::vector<int> & result) {
	if (node) {
		in_order_helper(node->left, result);
		result.push_back(node->val);
		in_order_helper(node->right, result);
	}
}


std::vector<int> Tree::pre_order(Tree_node * node) {
	std::vector<int> result;
	if (!root) {
		return result;
	}
	else {
		node ? pre_order_helper(node, result) : pre_order_helper(root, result);
	}
	return result;
}


void Tree::pre_order_helper(Tree_node * node, std::vector<int> & result) {
	if (node) {
		result.push_back(node->val);
		pre_order_helper(node->left, result);
		pre_order_helper(node->right, result);
	}
}


std::vector<int> Tree::post_order(Tree_node * node) {
	std::vector<int> result;
	if (!root) {
		return result;
	}
	else {
		node ? post_order_helper(node, result) : post_order_helper(root, result);
	}
	return result;
}


void Tree::post_order_helper(Tree_node * node, std::vector<int> & result) {
	if (node) {
		post_order_helper(node->left, result);
		post_order_helper(node->right, result);
		result.push_back(node->val);
	}
}


#pragma endregion
#pragma region GET DEPTH


int Tree::get_depth(Tree_node * node) {
	if (!node) {
		node = root;
	}
	std::vector<int> depth_vec;
	int depth = 1;
	int max = 1;
	get_depth_helper(node, depth, max);
	return max;
}


void Tree::get_depth_helper(Tree_node * root, int depth,  int & max) {
	if (depth > max) {
		max = depth;
	}
	if (root->left) {
		get_depth_helper(root->left, depth + 1, max);
	}
	if (root->right) {
		get_depth_helper(root->right, depth + 1, max);
	}
}


#pragma endregion
#pragma region MINIMAL TREE


void Tree::min_depth_tree(std::vector<int> vec) {
	if (vec.size() == 0) {
	}
	else if (vec.size() == 1 || vec.size() == 2) {
		for (int i = vec.size() - 1; i >= 0; --i) {
			insert(vec[i]);
		}
	}
	else {
		int middle = (vec.size() / 2);
		insert(vec[middle]);
		std::vector<int> left_vec;
		for (int i = 0; i < middle; ++i) {
			left_vec.push_back(vec[i]);
		}
		std::vector<int> right_vec;
		for (int i = middle + 1; i < vec.size(); ++i) {
			right_vec.push_back(vec[i]);
		}
		min_depth_tree(left_vec);
		min_depth_tree(right_vec);
	}
}


#pragma endregion
#pragma region LIST OF DEPTHS

typedef std::vector<std::vector<Tree_node *>> node_list;


node_list Tree::list_of_depths() {
	node_list depths;
	std::vector<Tree_node *> root_depth;
	if (!root) {
		return depths;
	}
	root_depth.push_back(root);
	depths.push_back(root_depth);
	int depth = 0;
	bool done = false;
	while (!done) {
		done = true;
		std::vector<Tree_node *> current_depth;
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


#pragma endregion
#pragma region IS BALANCED


bool Tree::is_balanced() {
	bool balanced = true;
	is_balanced_helper(balanced, root);
	return balanced;
}


void Tree::is_balanced_helper(bool & balanced, Tree_node * root) {
	int left_depth = 0;
	int right_depth = 0;
	if (root->left) {
		left_depth = get_depth(root->left);
	}
	if (root->right) {
		right_depth = get_depth(root->right);
	}
	if (left_depth + 1 < right_depth || left_depth > right_depth + 1) {
		balanced = false;
	}
	if (balanced) {
		if (root->left) {
			is_balanced_helper(balanced, root->left);
		}
		if (root->right) {
			is_balanced_helper(balanced, root->right);
		}
	}
}


#pragma endregion
#pragma region SUCCESSOR


Tree_node * Tree::get_successor(int val) {
	Tree_node * node = get_node(val);
	Tree_node * successor;
	if (node->right) {
		successor = follow_right_subtree(node);
	}
	else {
		if (node == root) {
			return nullptr;
		}
		successor = follow_parent_nodes(node);
	}
	return successor;
}


Tree_node * Tree::follow_right_subtree(Tree_node * node) {
	node = node->right;
	while (node->left) {
		node = node->left;
	}
	return node;
}


Tree_node * Tree::follow_parent_nodes(Tree_node * node) {
	Tree_node * prev = get_prev_node(node);
	while (prev != root) {
		if (node == prev->left) {
			return prev;
		}
		node = prev;
		prev = get_prev_node(prev);
	}
	return nullptr;
}


#pragma endregion
#pragma region GET SHARED PARENT


Tree_node * Tree::get_shared_parent(Tree_node * node_one, Tree_node * node_two) {
	Tree_node * result = get_shared_parent_helper(node_one, node_two, root);
	return result;
}


Tree_node * Tree::get_shared_parent_helper(Tree_node * node_one, Tree_node * node_two, Tree_node * it) {
	if (covers(node_one, it->left) == covers(node_two, it->right)) {
		return it;
	}
	else if (it == node_one || it == node_two) {
		return it;
	}
	else {
		bool one_on_left = covers(node_one, it->left);
		bool two_on_left = covers(node_two, it->right);
		if (one_on_left != two_on_left) {
			return it;
		}
		Tree_node * childside;
		childside = one_on_left ? it->left : it->right;
		return get_shared_parent_helper(node_one, node_two, childside);
	}
}


bool Tree::covers(Tree_node * search_node, Tree_node * current) {
	if (current == search_node) {
		return true;
	}
	else if (current == nullptr) {
		return false;
	}
	else {
		bool left = covers(search_node, current->left);
		bool right = covers(search_node, current->right);
		return left || right;
	}
}


#pragma endregion
#pragma region BST SEQUENCES

typedef std::vector<std::list<int>> list_vector;


list_vector Tree::bst_sequences() {
	if (root == nullptr) {
		list_vector sequences;
		std::list<int> first;
		sequences.push_back(first);
		return sequences;
	}
	list_vector result = bst_sequences_helper(root);
	return result;
}


list_vector Tree::bst_sequences_helper(Tree_node * root) {
	list_vector return_list;
	
	if (!root->left && !root->right) {
		list_vector result_list = { std::list<int>(root->val) };
		return return_list;
	}
	else if (!root->left || !root->right) {
		Tree_node * childnode;
		root->left ? childnode = root->left : childnode = root->right;
		list_vector list = bst_sequences_helper(childnode);
		return list;
	}
	else {
		list_vector result;
		std::list<int> prefix;
		list_vector left_list = bst_sequences_helper(root->left);
		list_vector right_list = bst_sequences_helper(root->right);
		for (auto left_it : left_list) {
			for (auto right_it : right_list) {
				weave(left_it, right_it, prefix, result);
			}
		}
		return result;
	}
}


void Tree::weave(std::list<int> left, std::list<int> right, std::list<int> prefix, std::vector<std::list<int>> & result) {
	if (left.empty() || right.empty()) {
		std::list<int> full_list;
		left.empty() ? full_list = left : full_list = right;
		for (int i : full_list) {
			prefix.push_back(i);
		}
	}
	else {
		int left_first = left.front();
		left.pop_front();
		prefix.push_back(left_first);
		weave(left, right, prefix, result);
		left.push_front(left_first);

		int right_first = right.front();
		right.pop_front();
		prefix.push_back(right_first);
		weave(left, right, prefix, result);
		right.push_back(right_first);
	}
}


#pragma endregion
#pragma region IS SUBTREE


bool Tree::is_subtree(Tree_node bigger, Tree_node smaller) {
	Tree_node * root_node = find_subtree(bigger, smaller);
	std::vector<int> bigger_list = pre_order(root_node);
	std::vector<int> smaller_list = pre_order(&smaller);
	if (bigger_list == smaller_list) {
		return true;
	}
	return false;
}


Tree_node * Tree::find_subtree(Tree_node bigger, Tree_node smaller) {
	bool same_node = false;
	while (!same_node) {
		if (bigger.val == smaller.val) {
			same_node = true;
		}
		else if (bigger.left->val < smaller.val && bigger.right->val > smaller.val) {
			return nullptr;
		}
		else {
			if (smaller.val < bigger.left->val) {
				bigger = *bigger.left;
			}
			else if (smaller.val > bigger.right->val) {
				bigger = *bigger.right;
			}
		}
	}
	return &bigger;
}


#pragma endregion
#pragma region RANDOM NODE


int Tree::random_node(Tree_node * node) {
	std::vector<int> ordered_nodes = in_order();
	int random_node = rand() % ordered_nodes.size();
	return ordered_nodes[random_node];
}


#pragma endregion
#pragma region PATH SUM


int Tree::paths_with_sum(int val) {
	std::vector<int> sums;
	int count = 0;
	paths_with_sum_helper(root, sums, count, val);
	return count;
}


void paths_with_sum_helper(Tree_node * node, std::vector<int> sums, int & count, int val) {
	if (node) {
		if (node->val == val) {
			++count;
		}
		for (int sum : sums) {
			sum += node->val;
			if (sum == val) {
				++count;
			}
		}
		sums.push_back(node->val);
		paths_with_sum_helper(node->left, sums, count, val);
		paths_with_sum_helper(node->right, sums, count, val);
	}
}


#pragma endregion