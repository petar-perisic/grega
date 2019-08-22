#ifndef GREGA_HPP_
#define GREGA_HPP_

#include "instruction.hpp"
#include "graph.hpp"
#include "node.hpp"
#include <vector>
#include <string>

class grega {
public:
    graph static build(std::vector<instruction> & instruction_set);
    void static simplify_spill(graph & G);

    static std::vector<node> spill_nodes;
    static int reg_num;
};

#endif // GREGA_HPP_