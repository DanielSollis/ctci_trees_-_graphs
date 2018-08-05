#include "tree.h"
#include "matrix_graph.h"
#include "list_graph.h"
#include "avl_tree.h"
#include <iostream>



int main() {
	AVL_Tree test_tree;
	for (int i = 10; i >= 1; --i) {
		test_tree.insert(i);
	}

	std::vector<std::vector<AVL_node *>> depths = test_tree.get_levels();
	for (auto depth : depths) {
		for (auto node : depth) {
			std::cout << node->data << " ";
		}
		std::cout << std::endl;
	}
	return 0;
}
