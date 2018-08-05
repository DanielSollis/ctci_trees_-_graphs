#pragma once
#include <vector>


struct AVL_node {
	int data;
	int height;
	AVL_node * left;
	AVL_node * right;
	AVL_node * parent;
};


class AVL_Tree {
	private:
		AVL_node * root = nullptr;

		void do_rotations(AVL_node * z, AVL_node * y, AVL_node * x);
		void left_rotation(AVL_node * pivot);
		void right_rotation(AVL_node * pivot);
	public:
		void insert(int val);
		bool remove(int val);
		AVL_node * search(int val);
		std::vector<std::vector<AVL_node *>> get_levels();
};