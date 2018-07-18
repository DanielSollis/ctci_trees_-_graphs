#include <memory>

struct Node {
	int val;
	Node * left = nullptr;
	Node * right = nullptr;
};


class Binary_search_tree {
private:
	Node * root;

	void destructor_helper(Node * root);
	void insert_helper(Node *& root, int val);
	void delete_leaf(Node * temp);
	void delete_single_parent(Node * temp);
	void delete_double_parent(Node * temp);
	Node * get_node(int val);
	Node * get_prev_node(Node * temp);
	void in_order_helper(Node * root);
	void pre_order_helper(Node * root);
	void post_order_helper(Node * root);
public:
	Binary_search_tree();
	~Binary_search_tree();
	void insert(int val);
	bool remove(int val);
	bool search(int val);
	void in_order();
	void pre_order();
	void post_order();
};