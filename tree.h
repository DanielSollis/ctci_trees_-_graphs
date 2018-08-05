#include <memory>
#include <vector>
#include <list>

struct Tree_node {
	int val;
	Tree_node * left = nullptr;
	Tree_node * right = nullptr;
};


class Tree {
private:
	Tree_node * root;

	void destructor_helper(Tree_node * root);
	void insert_helper(Tree_node *& root, int val);
	void delete_leaf(Tree_node * temp);
	void delete_single_parent(Tree_node * temp);
	void delete_double_parent(Tree_node * temp);
	Tree_node * get_node(int val);
	Tree_node * get_prev_node(Tree_node * temp);

	void in_order_helper(Tree_node * node, std::vector<int> & result);
	void pre_order_helper(Tree_node * node, std::vector<int> & result);
	void post_order_helper(Tree_node * node, std::vector<int> & result);

	void is_balanced_helper(bool & balanced, Tree_node * root);
	Tree_node * follow_right_subtree(Tree_node * node);
	Tree_node * follow_parent_nodes(Tree_node * node);
	void get_depth_helper(Tree_node * root, int depth, int & max);
	Tree_node * get_shared_parent_helper(Tree_node * node_one, Tree_node * node_two, Tree_node * it);
	bool covers(Tree_node * search_node, Tree_node * current);
	std::vector<std::list<int>> bst_sequences_helper(Tree_node * root);
	void weave(std::list<int> left, std::list<int> right, std::list<int> prefix, std::vector<std::list<int>> & result);
	Tree_node * find_subtree(Tree_node bigger, Tree_node smaller);
public:
	Tree();
	~Tree();
	void insert(int val);
	bool remove(int val);
	bool search(int val);
	std::vector<int> in_order(Tree_node * node = nullptr);
	std::vector<int> pre_order(Tree_node * node = nullptr);
	std::vector<int> post_order(Tree_node * node = nullptr);
	int get_depth(Tree_node * node = nullptr);
	std::vector<std::vector<Tree_node *>> list_of_depths();
	void min_depth_tree(std::vector<int> vec);
	bool is_balanced();
	Tree_node * get_successor(int val);
	Tree_node * get_shared_parent(Tree_node * node_one, Tree_node * node_two);
	std::vector<std::list<int>> bst_sequences();
	bool is_subtree(Tree_node bigger, Tree_node smaller);
	int random_node(Tree_node * node = nullptr);
	int paths_with_sum(int sum);
};