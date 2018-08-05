#pragma once
#include "list_graph.h"


vector<char> List_graph::build_order(vector<char> projects, vector<pair<char, char>> dependencies) {
	graph = get_dependency_graph(projects, dependencies);
	vector<char> order;
	bool done = false;
	while (!done || order.size() == projects.size()) {
		done = add_dependencies(projects);
	}
	if (!done) {
		vector<char> empty;
		return empty;
	}
	return order;
}


unordered_map<char, vector<char>> List_graph::get_dependency_graph(vector<char> projects, vector<pair<char, char>> dependencies) {
	unordered_map<char, vector<char>> graph;
	for (char project : projects) {
		vector<char> temp;
		graph.emplace(project, temp);
	}
	for (auto dep : dependencies) {
		graph[dep.first].push_back(dep.second);
	}
	return graph;
}


bool List_graph::add_dependencies(vector<char> & order) {
	bool done = true;
	for (auto project : graph) {
		if (project.second.size() == 0) {
			order.push_back(project.first);
			done = false;
			for (auto pass_two : graph) {
				vector<char>::iterator position = find(project.second.begin(), project.second.end(), pass_two.first);
				if (position != project.second.end()) {
					project.second.erase(position);
				}
			}
		}
	}
	return done;
}