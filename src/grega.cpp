#include "../include/grega.hpp"
#include "../include/node.hpp"

#include <iostream>

graph grega::build(std::vector<instruction> & instruction_set)
{
    graph G;
    for (auto & i : instruction_set) {
        G.add_node(node(i.var()));

        for (auto & u : i.use()) {
            G.add_edge(node(i.var()), node(u));
        }
    }

    #ifdef DEBUG
    for (auto u : G.nodes()) {
        std::cout << "node: " << u.name() << ", degree: " << u.degree(G.adjacency_list()) << std::endl; 
    }
    #endif // DEBUG
    
    return G;
}
