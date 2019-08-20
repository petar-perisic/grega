#ifndef GRAPH_HPP_
#define GRAPH_HPP_
#include <string>
#include <vector>

class Graph{
public:
	Graph(int num_of_nodes, int num_of_egdes);
	Graph();
<<<<<<< HEAD
=======
	~Graph();
>>>>>>> c24fe00eabf46f2a77fed8a3563fd1cf2e950b1d
	void add_edge(char A, char B);
	void add_node(char A);
	void remove_edge(char A, char B);
	void remove_node(char A);	
	bool contains_edge(char A, char B);
	bool contains_node(char A);
	bool edge_equal(std::pair<char, char> a, std::pair<char, char> b);
	void print_graph();


private:
	std::vector<std::pair<char, char>> m_edges;
	std::vector<char> m_nodes;
};


#endif // GRAPH_HPP_