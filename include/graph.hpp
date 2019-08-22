#ifndef GRAPH_HPP_
#define GRAPH_HPP_

#include "node.hpp"

#include <string>
#include <vector>

class graph {
public:
	graph();
	graph(int num_of_nodes, int num_of_egdes);

	void add_edge(node a, node b);
	void add_node(node a);
	
	void remove_edge(node a, node b);
	void remove_node(node a);	
	
	bool contains_edge(node a, node b);
	bool contains_node(node a);
	
	bool edge_equal(std::pair<node, node> a, std::pair<node, node> b);
	
	void print_graph();

	std::vector<std::pair<node, node>> adjacency_list() const;
	std::vector<node> nodes() const;

private:
	std::vector<std::pair<node, node>> m_edges;
	std::vector<node> m_nodes;
};

#endif // GRAPH_HPP_