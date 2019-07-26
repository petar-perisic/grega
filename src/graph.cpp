#include "graph.hpp"

#include <algorithm>
#include <iostream>

namespace grega {

graph::graph()
{
}

void graph::add_edge(const int u, const int v)
{
    adjacency_list.fi
}

void graph::print() const
{
    for (size_t i = 0; i < adjacency_list.size(); i++) {
        std::cout << adjacency_list[i] << ": ";
    }
    
}

} // namespace grega