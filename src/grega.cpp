#include "../include/grega.hpp"
#include "../include/node.hpp"

#include <iostream>

#define DEBUG

// initialize static members
std::vector<node> grega::spill_nodes;
int grega::reg_num = 4;

graph grega::build(std::vector<instruction> & instruction_set)
{
    spill_nodes.resize(0);

    graph G;
    for (auto & i : instruction_set) {
        G.add_node(node(i.var()));

        for (auto & u : i.use()) {
            G.add_edge(node(i.var()), node(u));
            G.find_node(i.var()).adjacent_nodes().push_back(node(u));
        }
    }

    #ifdef DEBUG
    for (auto u : G.nodes()) {
        std::cout << "node: " << u.name() << ", degree: " << u.degree(G.adjacency_list()) << std::endl; 
        std::cout << std::endl;
    }
    #endif // DEBUG
    
    return G;
}

void grega::simplify_spill(graph & G)
{
    for (auto & i : G.nodes()) {
        i.degree(G.adjacency_list());

        if (i.degree() >= reg_num)
            i.is_spilled(true);

        for (auto & edge : G.adjacency_list()) {
            if (G.contains_edge(i, edge.first)) {
                G.remove_edge(i, edge.first);
            } else if (G.contains_edge(i, edge.second)) {
                G.remove_edge(i, edge.second);
            }
        }

        spill_nodes.push_back(i);
        G.remove_node(i);
    }

    #ifdef DEBUG
    for (auto & i : spill_nodes) {
        std::cout << i.name() << ", is spilled: " << i.is_spilled() << std::endl;
        
        std::cout << "\t adjacent_nodes: ";
        for (auto &u : i.adjacent_nodes()) {
            std::cout << u.name() << " ";
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;
    
    if (G.nodes().empty())
        std::cout << "Graph is empty!" << std::endl;

        std::cout << std::endl;
    #endif //DEBUG
}
