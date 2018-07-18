#include <vector>

class Graph{
private:
	std::vector<std::vector<bool>> adjacency_matrix;
	
	void resize_matrix(int size);
	bool set_node(std::vector<int> edges, int node);
public:
	Graph();
	bool get_graph_input();
	void print_matrix();
	bool route_between_nodes();
};