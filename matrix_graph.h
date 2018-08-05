#include <vector>
#include <unordered_set>

class Matrix_graph{
private:
	std::vector<std::vector<bool>> adjacency_matrix;
	typedef std::vector<std::pair<char, char>> dependency_list;
	
	void resize_matrix(int size);
	bool set_node(std::vector<int> edges, int node);
	void set_default_matrix(int size);
	
public:
	Matrix_graph();
	bool get_graph_input();
	void print_matrix();
	bool route_between_nodes(int start_node, int end_node);
	std::vector<char> build_order(std::unordered_set<char> projects, dependency_list dependencies);
};