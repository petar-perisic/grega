#include "../include/grega.hpp"
#include "../include/node.hpp"

#include <algorithm>
#include <iostream>
#include <numeric>

// #define DEBUG

// initialize static members
std::vector<node> grega::spill_nodes;
int grega::reg_num = 4;
std::vector<instruction> grega::instruction_set;

void grega::liveness_analysis()
{
    int size = instruction_set.size();
    for (auto i = instruction_set.rbegin(); i != instruction_set.rend(); i++) {
        if (i != instruction_set.rbegin())
            i->use() = (i - 1)->use();
        
        // remove variable from the left hand side
        auto del = std::find(i->use().begin(), i->use().end(), i->var());
        if (del != i->use().end())
            i->use().erase(del);

        // add operators on the right hand side
        if (i->size() == 3) {
            if (!i->is_move_op1())
                i->use_list_add_if_unique(i->operand1());
            if (!i->is_move_op2())
                i->use_list_add_if_unique(i->operand2());
        } else {
            if (!i->is_move_op1())
                i->use_list_add_if_unique(i->operand1());
        }

        #ifdef DEBUG 
        std::cout << "Liveness analysis:" << std::endl;
        std::cout << size-- << ". " << i->to_string() << std::endl;
        i->print_use_list();
        #endif // DEBUG
    }
}

graph grega::build()
{
    spill_nodes.resize(0);

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
        if (!grega::color(G.find_node(u.name()), G)) {
            start_over(u);
            return;
        }
    }
}

void grega::start_over(node u)
{
    for (auto & i : instruction_set) {
        if (i.size() == 3) {
            if (!i.var().compare(u.name())) {
                i.is_move_var(true);
            } else if (!i.operand1().compare(u.name())) {
                i.is_move_op1(true);
            } else if (!i.operand2().compare(u.name())) {
                i.is_move_op2(true);
            }
        } else {
           if (!i.var().compare(u.name())) {
                i.is_move_var(true);
            } else if (!i.operand1().compare(u.name())) {
                i.is_move_op1(true);
            }
        }
    }
}

void grega::print(graph & G)
{
    int instruction_counter = 1;
    for (auto & i : instruction_set) {
        if (i.size() == 3) {
            // first, print move instruction if needed
            std::vector<std::string> vars_move;
            if (i.is_move_var())
                vars_move.push_back(i.var());
            if (i.is_move_op1())
                vars_move.push_back(i.operand1());
            if (i.is_move_op2())
                vars_move.push_back(i.operand2());

            if (!vars_move.empty()) {
                std::cout << "   move: ";
                for (auto & var : vars_move)
                    std::cout << var << " ";
                std::cout << std::endl;
            }
            
            std::cout << instruction_counter++ << ". ";

            // print var
            if (i.is_move_var())
                std::cout << i.var() << " := ";
            else
                std::cout << "r" << G.find_node(i.var()).color() << " := ";
            
            // print operand 1
            if (i.is_move_op1())
                std::cout << i.operand1();
            else
                std::cout << "r" << G.find_node(i.operand1()).color();

            // print operator
            std::cout << " " << i.instruction_operator() << " ";
            
            // print operand 2
            if (i.is_move_op2())
                std::cout << i.operand2();
            else
                std::cout << "r" << G.find_node(i.operand2()).color();

            std::cout << std::endl;

            if (!vars_move.empty()) {
                std::cout << "   move: ";
                for (auto & var : vars_move)
                    std::cout << var << " ";
                std::cout << "\n" << std::endl;
            }
        } else { // instruction size = 1
            std::vector<std::string> vars_move;
            if (i.is_move_var())
                vars_move.push_back(i.var());
            if (i.is_move_op1())
                vars_move.push_back(i.operand1());

            if (!vars_move.empty()) {
                std::cout << "   move: ";
                for (auto & var : vars_move)
                    std::cout << var << " ";
                std::cout << std::endl;
            }

            std::cout << instruction_counter++ << ". ";

            if (i.is_move_var())
                std::cout << i.var() << " := ";
            else
                std::cout << "r" << G.find_node(i.var()).color() << " := ";
            
            if (i.is_move_op1())
                std::cout << i.operand1();
            else
                std::cout << "r" << G.find_node(i.operand1()).color();

            std::cout << std::endl;

            if (!vars_move.empty()) {
                std::cout << "   move: ";
                for (auto & var : vars_move)
                    std::cout << var << " ";
                std::cout << "\n" << std::endl;
            }
        }
    }
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