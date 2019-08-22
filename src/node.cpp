#include "../include/node.hpp"

#include <vector>
#include <string>

node::node()
{}

node::node(std::string name)
    : m_name(name)
{}

void node::name(std::string node_name)
{
    m_name = node_name;
}

std::string node::name() const
{
    return m_name;
}

void node::color(std::string col)
{
    m_color = col;
}

std::string node::color() const
{
    return m_color;
}

int node::degree(std::vector<std::pair<node, node>> adjacency_list)
{
    for (auto & i : adjacency_list) {
        if (!m_name.compare(i.first.name()) || !m_name.compare(i.second.name()))
            m_degree++;
    }
    
    return m_degree;
}

int node::degree() const
{
    return m_degree;
}

bool node::operator==(const node & other) const
{
    return this->m_name.compare(other.m_name) == 0;
}

void node::is_spilled(bool option)
{
    m_is_spilled = option;
}

bool node::is_spilled() const
{
    return m_is_spilled;
}

std::vector<node> & node::adjacent_nodes()
{
    return m_adjacent_nodes;
}
