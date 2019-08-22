#include "../include/grega.hpp"

Graph grega::build(std::vector<instruction> & instruction_set)
{
    Graph G;
    for (auto & i : instruction_set) {
        G.add_node(i.var());
        for (auto & u : i.use()) {
            G.add_edge(i.var(), u);
        }
    }

    return G;
}
