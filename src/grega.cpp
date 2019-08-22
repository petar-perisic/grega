#include "../include/grega.hpp"
#include "../include/node.hpp"

#include <algorithm>
#include <iostream>
#include <numeric>

#define DEBUG

// initialize static members
std::vector<node> grega::spill_nodes;
int grega::reg_num = 4;
std::vector<instruction> grega::instruction_set;

graph grega::build(std::vector<instruction> & instruction_set)
{
    spill_nodes.resize(0);

    grega::instruction_set = instruction_set;

    graph G;
    for (auto & i : grega::instruction_set) {
        G.add_node(node(i.var()));
        auto u = G.find_node(i.var());
        
        for (auto & v : i.use())
            G.add_edge(u, node(v));
    }

    G.update_adjacent_nodes_list();

    #ifdef DEBUG
    std::cout << "  \n----- Build:\n" << std::endl;

    for (auto u : G.nodes()) {

        std::cout << "node: " << u.name() << ", degree: " << u.degree(G.adjacency_list()) << std::endl; 
        std::cout << std::endl;
    }
    
    G.print_graph();

    for (auto & n : G.nodes()) {
        std::cout << n.name() << std::endl;
        
        std::cout << "   adjacent_nodes: ";
        for (auto & u : n.adjacent_nodes()) {
            std::cout << u.name() << " ";
        }

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
    std::cout << "  \n----- Simplify and Spill:\n" << std::endl;

    for (auto & i : spill_nodes) {
        std::cout << i.name() << ", is spilled: " << i.is_spilled() << std::endl;
        std::cout << std::endl;
    }
    
    std::cout << std::endl;
    
    if (G.nodes().empty())
        std::cout << "Graph is empty!" << std::endl;
    #endif //DEBUG
}

void grega::select(graph & G)
{
    #ifdef DEBUG
    std::cout << "  \n----- Select:\n" << std::endl;
    #endif //DEBUG

    while (!spill_nodes.empty()) {
        // add node
        auto u = spill_nodes.back();
        
        G.add_node(u);
        
        spill_nodes.pop_back();
        
        // add edges
        for (auto & v : u.adjacent_nodes()) {
            G.add_edge(u, v);
        }

        // color
        if (!grega::color(G.find_node(u.name()), G))
            start_over(u);
    }
}

void grega::start_over(node u)
{

}

void grega::print(const graph & G)
{

}

bool grega::color(node & u, graph & G)
{
    std::vector<int> registers(reg_num);
    std::iota(registers.begin(), registers.end(), 1);
    
    for (auto & v : G.adjacency_list()) {
        if (G.contains_edge(u, v.first)) {
            erase_color(registers, G.find_node(v.first.name()).color());
        } else if (G.contains_edge(u, v.second)) {
            erase_color(registers, G.find_node(v.second.name()).color());
        }
    }
    
    if (!registers.empty()) {
        u.color(registers.front());

        #ifdef DEBUG
        std::cout << u.name() << " : color = r" << u.color() << std::endl;
        #endif // DEBUG

        return true;
    } else {
        #ifdef DEBUG
        std::cout << "Failed to add color for node: " << u.name() << "!" << std::endl;
        #endif // DEBUG

        return false;
    }
}

void grega::erase_color(std::vector<int> & colors, int color)
{
    for (auto i = std::begin(colors); i != std::end(colors); i++) {
        if (*i == color) {
            colors.erase(i);
            return;
        }
    }
}