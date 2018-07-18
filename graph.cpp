#include "graph.h"
#include <iostream>

std::vector<int> get_edges(int node);

#pragma region CONSTRUCTOR


Graph::Graph() {
	std::vector<std::vector<bool>> default_matrix = { 
		{ 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0 },
	};
	adjacency_matrix = default_matrix;
}


#pragma endregion
#pragma region SET GRAPH


bool Graph::get_graph_input() {
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


void Graph::resize_matrix(int size) {
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


bool Graph::set_node(std::vector<int> edges, int node) {
	for (int edge : edges) {
		if (edge > adjacency_matrix.size()) {
			return false;
		}
		adjacency_matrix[node - 1][edge - 1] = true;
	}
	return true;
}


#pragma endregion
#pragma region PRINT


void Graph::print_matrix() {
	for (int i = 0; i < adjacency_matrix.size(); ++i) {
		for (auto cell : adjacency_matrix[i]) {
			std::cout << cell << " ";
		}
		std::cout << "\n";
	}
}


#pragma endregion


bool Graph::route_between_nodes() {

}