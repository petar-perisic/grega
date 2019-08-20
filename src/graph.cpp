#include "../include/graph.hpp"
#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>
#include <utility>
#include <cctype>

Graph::Graph(int num_of_nodes, int num_of_egdes)
: m_nodes(num_of_nodes)
{
	m_edges = std::vector<std::pair<char, char>>(num_of_egdes);
}
Graph::Graph()
: m_nodes(0)
{
	m_edges = std::vector<std::pair<char, char>>(0);
}
//~Graph(){}
void Graph::add_edge(char A, char B)
{
	A = toupper(A);
	B = toupper(B);

	if((contains_node(A)) && (contains_node(B)))
	{
		if(!this->contains_edge(A, B))
		{
			auto ab = std::make_pair(A, B);
			m_edges.push_back(ab);
		}
	} 
	else
	{
		std::cout << "Pokusano dodavanje grane u vektor grana a da cvorovi nisu vec u vektoru cvorova!" << std::endl;
		std::cout << "Moguce resenje: Dodaj automatsko dodavanje cvorova, ako zelis da dodajes granu automatski!" << std::endl;
	}
}
void Graph::add_node(char A)
{
	A = toupper(A);
	if(!contains_node(A))
	{
		m_nodes.push_back(A);
	} // else - it already exists 
}
void Graph::remove_edge(char A, char B)
{
	A = toupper(A);
	B = toupper(B);

	auto ab = std::make_pair(A, B);
	std::vector<std::pair<char, char>>::iterator it = std::find(m_edges.begin(), m_edges.end(), ab);
	if(it != m_edges.end())
	{
		m_edges.erase(it);
	}
	else
	{
		auto ba = std::make_pair(A, B);
		std::vector<std::pair<char, char>>::iterator it2 = std::find(m_edges.begin(), m_edges.end(), ba);
		if(it != m_edges.end())
		{
			m_edges.erase(it2);
		}
		else
		{
			std::cout << "Can't remove edge that isn't already in the `m_edges` vector!" << std::endl;
		}
	}
}

void Graph::remove_node(char A)
{
	A = toupper(A);
	
	if(this->contains_node(A))
	{
		m_nodes.erase(std::find(m_nodes.begin(), m_nodes.end(), A));
	}
	else
	{
		std::cout << "Can't remove node that isn't already in the `m_nodes` vector!" << std::endl;
	}
}

bool Graph::contains_edge(char A, char B)
{
	A = toupper(A);
	B = toupper(B);
	auto ab = std::make_pair(A, B);
	auto ba = std::make_pair(B, A);
	for(auto pair : m_edges)
	{
		if(edge_equal(pair, ab) || (edge_equal(pair, ba))) 
		{
			return true;
		}
	}
	return false;
}

bool Graph::contains_node(char A)
{
	A = toupper(A);

	auto it = std::find(m_nodes.begin(), m_nodes.end(), A);
	if(it != m_nodes.end())
	{
		return true;
	}

	return false;
}

bool Graph::edge_equal(std::pair<char, char> a, std::pair<char, char> b)
{
	if((a.first == b.first && a.second == b.second) 
		|| (a.first == b.second && a.second == b.first))
	{
		return true;
	}
	return false;
}	
void Graph::print_graph()
{
	std::cout << "You wanted graph presentation, so here you go:" << std::endl;
	std::cout << "Nodes:" << std::endl; 

	for(auto n : m_nodes)
	{
		std::cout << n << " ";
	}
	std::cout << std::endl;
	
	std::cout << std::endl << "Edges:" << std::endl; 

	int i = 0;
	for(auto e : m_edges)
	{
		std::cout << e.first << "-" << e.second << "  ";
		i++;
		if(i % 5 == 0) 
		{
			std::cout << std::endl;
		}
	}
	std::cout << std::endl;


}

