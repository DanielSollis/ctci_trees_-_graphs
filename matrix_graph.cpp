#include "matrix_graph.h"
#include <iostream>
#include <queue>

typedef std::vector<std::pair<char, char>> dependency_list;

std::vector<int> get_edges(int node);

#pragma region CONSTRUCTOR


Matrix_graph::Matrix_graph() {
	std::vector<std::vector<bool>> default_matrix = { 
		{ 0, 1, 0, 0, 0 },
		{ 1, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0 },
	};
	adjacency_matrix = default_matrix;
}


#pragma endregion
#pragma region SET GRAPH


bool Matrix_graph::get_graph_input() {
	std::cout << "How many Nodes are in the graph? ";
	int node_num;
	std::cin >> node_num;
	resize_matrix(node_num);
	for (int i = 1; i <= node_num; ++i) {
		std::vector<int> edges = get_edges(i);
		set_node(edges, i);
	}
	return true;
}


void Matrix_graph::resize_matrix(int size) {
	adjacency_matrix.resize(size);
	for (int i = 0; i < adjacency_matrix.size(); i++) {
		adjacency_matrix[i].resize(size);
	}
}


std::vector<int> get_edges(int node) {
	std::cout << "which Nodes does Node " << node << " connect to? \n";
	std::vector<int> edges;
	do
	{
		int input;
		if (std::cin >> input)
			edges.push_back(input);
	} while (std::cin && std::cin.peek() != '\n');
	return edges;
}


bool Matrix_graph::set_node(std::vector<int> edges, int node) {
	for (int edge : edges) {
		if (edge > adjacency_matrix.size()) {
			return false;
		}
		adjacency_matrix[node - 1][edge - 1] = true;
	}
	return true;
}


void Matrix_graph::set_default_matrix(int size) {
	adjacency_matrix.resize(size);
	for (auto row : adjacency_matrix) {
		for (auto cell : row) {
			cell = 0;
		}
	}
}


#pragma endregion
#pragma region PRINT


void Matrix_graph::print_matrix() {
	for (int i = 0; i < adjacency_matrix.size(); ++i) {
		for (auto cell : adjacency_matrix[i]) {
			std::cout << cell << " ";
		}
		std::cout << "\n";
	}
}


#pragma endregion
#pragma region ROUTE BETWEEN NODES


bool Matrix_graph::route_between_nodes(int start_node, int end_node) {
	std::unordered_set<int> visited;
	std::queue<int> queue;
	queue.push(start_node);
	while (!queue.empty()) {
		if (!queue.empty()) {
			int start_current = queue.front();
			queue.pop();
			if (start_current == end_node) {
				return true;
			}
			visited.insert(start_current);
			for (int i = 1; i <= adjacency_matrix.size(); ++i) {
				if (adjacency_matrix[start_current - 1][i - 1] && visited.find(i) != visited.end()) {
					queue.push(i);
				}
			}
		}
	}
	return false;
};


#pragma endregion