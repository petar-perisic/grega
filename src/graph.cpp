#include "../include/graph.hpp"

#include <algorithm>
#include <iostream>
#include <optional>
#include <iterator>
#include <utility>
#include <vector>
#include <string>
#include <cctype>

graph::graph()
	: m_nodes(0)
{
	m_edges = std::vector<std::pair<node, node>>(0);
}

graph::graph(int num_of_nodes, int num_of_egdes)
	: m_nodes(num_of_nodes)
{
	m_edges = std::vector<std::pair<node, node>>(num_of_egdes);
}

void graph::add_edge(node a, node b)
{
	if((contains_node(a.name())) && (contains_node(b.name())))
	{
		if(!this->contains_edge(a.name(), b.name()))
		{
			auto ab = std::make_pair(a, b);
			m_edges.push_back(ab);
		}
	} 
	else
	{
		#ifdef DEBUG
		std::cout << "Adding non edge between non existing nodes!" << std::endl;
		#endif //DEBUG
	}
}

void graph::add_node(node a)
{
	if(!contains_node(a.name()))
	{
		m_nodes.push_back(a);
	} // else - it already exists 
}

void graph::remove_edge(node a, node b)
{
	auto ab = std::make_pair(a, b);

	auto it = std::find(m_edges.begin(), m_edges.end(), ab);
	if(it != m_edges.end())
	{
		m_edges.erase(it);
	}
	else
	{
		auto ba = std::make_pair(b, a);
		auto it2 = std::find(m_edges.begin(), m_edges.end(), ba);
		if(it2 != m_edges.end())
		{
			m_edges.erase(it2);
		}
		else
		{
			#ifdef DEBUG
			std::cout << "Can't remove edge that isn't already in the `m_edges` vector!" << std::endl;
			#endif // DEBUG
		}
	}
}

void graph::remove_node(node a)
{
	if(this->contains_node(a))
	{
		m_nodes.erase(std::find(m_nodes.begin(), m_nodes.end(), a));
	}
	else
	{
		#ifdef DEBUG
		std::cout << "Can't remove node that isn't already in the `m_nodes` vector!" << std::endl;
		#endif // DEBUG
	}
}

bool graph::contains_edge(node a, node b)
{
	auto ab = std::make_pair(a, b);
	auto ba = std::make_pair(b, a);

	for(auto pair : m_edges)
	{
		if(edge_equal(pair, ab) || (edge_equal(pair, ba))) 
		{
			return true;
		}
	}
	return false;
}

bool graph::contains_node(node a)
{
	auto it = std::find(m_nodes.begin(), m_nodes.end(), a);
	if(it != m_nodes.end())
	{
		return true;
	}

	return false;
}

bool graph::edge_equal(std::pair<node, node> a, std::pair<node, node> b)
{
	if((!a.first.name().compare(b.first.name())  && !a.second.name().compare(b.second.name())) ||
	   (!a.first.name().compare(b.second.name()) && !a.second.name().compare(b.first.name())))
	{
		return true;
	}
	return false;
}

void graph::print_graph()
{
	std::cout << "Nodes:" << std::endl; 

	for(auto n : m_nodes)
	{
		std::cout << n.name() << " ";
	}
	std::cout << std::endl;
	
	std::cout << std::endl << "Edges:" << std::endl; 

	int i = 0;
	for(auto e : m_edges)
	{
		std::cout << e.first.name() << "-" << e.second.name() << "  ";
		i++;
		if(i % 5 == 0) 
		{
			std::cout << std::endl;
		}
	}
	std::cout << std::endl;
}

std::vector<std::pair<node, node>> graph::adjacency_list() const
{
	return m_edges;
}

std::vector<node> graph::nodes() const
{
	return m_nodes;
}

node& graph::find_node(std::string node_name)
{
	for (auto & n : m_nodes) {
		if (n.name().compare(node_name) == 0)
			return n;
	}
	
	node not_found{};
	return not_found;
}

void graph::update_adjacent_nodes_list()
{
	for (auto & u : m_nodes) {
		for (auto & v : m_edges) {
			if (contains_edge(u, v.first)) {
				auto it = std::find(u.adjacent_nodes().begin(), u.adjacent_nodes().end(), v.first);
				if (it == u.adjacent_nodes().end())
					u.adjacent_nodes().push_back(v.first);
			}
			else if (contains_edge(u, v.second)) {
				auto it = std::find(u.adjacent_nodes().begin(), u.adjacent_nodes().end(), v.second);
				if (it == u.adjacent_nodes().end())
					u.adjacent_nodes().push_back(v.second);
			}
		}
		
	}
	
}
