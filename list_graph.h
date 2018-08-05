#pragma once
#include <algorithm>
#include <unordered_map>
#include <vector>


using std::vector;
using std::unordered_map;
using std::pair;


class List_graph {
private:
	unordered_map<char, vector<char>> graph;

	unordered_map<char, vector<char>> get_dependency_graph(vector<char> projects, vector<pair<char, char>> dependencies);
	bool add_dependencies(vector<char> & order);
public:
	vector<char> build_order(vector<char> projects, vector<pair<char, char>> dependencies);
};