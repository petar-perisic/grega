#ifndef GRAPH_HPP_
#define GRAPH_HPP_

#include <string>
#include <vector>

class Graph {
public:
	Graph();
	Graph(int num_of_nodes, int num_of_egdes);

	void add_edge(std::string A, std::string B);
	void add_node(std::string A);
	
	void remove_edge(std::string A, std::string B);
	void remove_node(std::string A);	
	
	bool contains_edge(std::string A, std::string B);
	bool contains_node(std::string A);
	
	bool edge_equal(std::pair<std::string, std::string> a, std::pair<std::string, std::string> b);
	
	void print_graph();

private:
	std::vector<std::pair<std::string, std::string>> m_edges;
	std::vector<std::string> m_nodes;
};

#endif // GRAPH_HPP_